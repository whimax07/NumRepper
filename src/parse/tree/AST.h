//
// Created by max on 25/07/22.
//

#ifndef REPPARSE_AST_H
#define REPPARSE_AST_H


#include <utility>
#include <variant>
#include <stack>
#include "../token/Token.h"
#include "../token/Operator.h"
#include "../token/Unary.h"
#include "../token/Binary.h"
#include "../token/NumericToken.h"


namespace repper {

typedef std::variant<TypedNumbers, Unary, Binary> NodeTypes;
//using NodeTypes = std::variant<NumericToken, Unary, Binary>;


class AST {

public:
    using AstSPtr = std::shared_ptr<AST>;


private:
    NodeTypes value_;

    AstSPtr left_;

    AstSPtr right_;


public:
    AST() : value_(), left_(), right_() {}

    explicit AST(NodeTypes value)
            : value_(std::move(value)), left_(), right_() {}

    AST(NodeTypes value, AstSPtr left)
            : value_(std::move(value)), left_(std::move(left)), right_() {}

    AST(NodeTypes value, AstSPtr left, AstSPtr right)
            : value_(std::move(value)), left_(std::move(left)),
              right_(std::move(right)) {}

    ~AST() = default;


public:
    friend bool operator==(const AST &lhs, const AST &rhs) {
        return isEqual(lhs, rhs);
    }

    friend bool operator!=(const AST &lhs, const AST &rhs) {
        return !isEqual(lhs, rhs);
    }

    [[nodiscard]]
    NodeTypes getValue() const {
        return value_;
    }

    void setValue(NodeTypes value) {
        auto temp = NodeTypes(std::move(value));
        swap(value_, temp);
    }

    [[nodiscard]] AstSPtr getLeft() const {
        return left_;
    }

    void setLeft(AstSPtr left) {
        left_ = std::move(left);
    }

    [[nodiscard]] AstSPtr getRight() const {
        return right_;
    }

    void setRight(AstSPtr right) {
        right_ = std::move(right);
    }


private:
    static bool isEqual(const AST &lhs, const AST &rhs) {
        if (!(lhs.value_ == rhs.value_)) {
            return false;
        }

        if (!lhs.left_ && !rhs.left_) {
            /* Keep checking. */
        } else if (lhs.left_ && rhs.left_) {
            auto isLeftEqual = isEqual(*lhs.left_, *rhs.left_);
            if (!isLeftEqual) return false;
        }  else {
            return false;
        }

        if (!lhs.right_ && !rhs.right_) {
            /* Keep checking. */
        } else if (lhs.right_ && rhs.right_) {
            auto isRightEqual = isEqual(*lhs.right_, *rhs.right_);
            if (!isRightEqual) return false;
        } else {
            return false;
        }

        return true;
    }


public:
    static TypedNumbers evaluate(const AST::AstSPtr& toEval) {
        auto nodeValue = toEval->getValue();
        return std::visit(Overloaded {toEval}, nodeValue);
    }

    static TypedNumbers evaluateNonRec(const AST::AstSPtr& toEval) {
        auto holdsNumber = [](const Result& in) { return std::holds_alternative<TypedNumbers>(in); };

        std::stack<EvalStage> stack;

        auto current = Result(toEval);
        auto left = Result(toEval->getLeft());
        auto right = Result(toEval->getRight());
        auto evalLeft = true;

        while (true) {
            if (holdsNumber(current)) {
                if (stack.empty()) {
                    return std::get<TypedNumbers>(current);
                }

                current = stack.top().source;
                if (evalLeft) {
                    left = current;
                    right = stack.top().right;
                } else {
                    left = stack.top().left;
                    right = current;
                }
                evalLeft = stack.top().evalLeft;

                continue;
            }

            auto ast = std::get<AstSPtr>(current);

            if (std::holds_alternative<Unary>(ast->value_)) {
                if (holdsNumber(left)) {
                    auto num = std::get<TypedNumbers>(left);
                    auto unary = std::get<Unary>(ast->value_);
                    current = unary.evalTypedNumber(num);
                    continue;
                }

                if (std::holds_alternative<AstSPtr>(left)) {
                    stack.push(EvalStage { current, left, right, evalLeft });
                    auto l = std::get<AstSPtr>(left);
                    current = l;
                    left = l->left_;
                    right = l->right_;
                    evalLeft = true;
                    continue;
                }

                throw std::logic_error("`left` has a type not accounted for.");
            }

            if (std::holds_alternative<Binary>(ast->value_)) {
                if (holdsNumber(left) && holdsNumber(right)) {
                    auto numL = std::get<TypedNumbers>(left);
                    auto numR = std::get<TypedNumbers>(right);
                    auto binary = std::get<Binary>(ast->value_);
                    current = binary.evalTypedNumber(numL, numR);
                    continue;
                }

                if (std::holds_alternative<AstSPtr>(left)) {
                    stack.push(EvalStage { current, left, right, evalLeft });
                    auto l = std::get<AstSPtr>(left);
                    current = l;
                    left = l->left_;
                    right = l->right_;
                    evalLeft = true;
                    continue;
                }

                if (std::holds_alternative<AstSPtr>(right)) {
                    stack.push(EvalStage { current, left, right, evalLeft });
                    auto r = std::get<AstSPtr>(right);
                    current = r;
                    left = r->left_;
                    right = r->right_;
                    evalLeft = false;
                    continue;
                }

                throw std::logic_error("One of `left` or `right` has a type not accounted for.");
            }

            throw std::logic_error("`current` holds a type not accounted for.");
        }
    }


private:
    using Result = std::variant<AstSPtr, TypedNumbers>;

    struct EvalStage {
        Result source;
        Result left;
        Result right;
        bool evalLeft;
    };

    struct Overloaded {
        const AST::AstSPtr& toEval;

        TypedNumbers operator()(TypedNumbers typedNumbers) {
            return typedNumbers;
        }

        TypedNumbers operator()(const Unary& nodeValue) {
            return std::visit(
                    [nodeValue](auto in) -> TypedNumbers {
                        return nodeValue.evalUnary(in);
                    },
                    // The recursion.
                    AST::evaluate(toEval->getLeft())
            );
        }

        TypedNumbers operator()(Binary nodeValue) {
            return std::visit(
                    [nodeValue](auto in1, auto in2) -> TypedNumbers {
                        return nodeValue.evalBinary(in1, in2);
                    },
                    // The recursion.
                    AST::evaluate(toEval->getLeft()),
                    AST::evaluate(toEval->getRight())
            );
        }

    };

};

}


#endif //REPPARSE_AST_H
