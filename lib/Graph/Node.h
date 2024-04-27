#pragma once

#include <type_traits>

static unsigned unique_id = -1;

// Type Erasure Idiom
class Node {
public:
    [[nodiscard]] inline const bool GetIsResultCalculated() const { return is_result_calculated; }
    [[nodiscard]] inline const unsigned GetNodeId() const { return id; }
    
    inline void SetResultAsCalculated() { is_result_calculated = true; }
    
public:
    [[nodiscard]] virtual const void* GetResult() const = 0;
    virtual void Calculate() = 0;
    
private:
    unsigned id = ++unique_id;
    bool is_result_calculated = false;
};

template <typename Expression, typename T>
class NodeBinaryExpression : public Node {
public:
    NodeBinaryExpression(Expression&& expression, const T& argument1, const T& argument2) :
        expression_(std::move(expression)),
        argument1_(argument1),
        argument2_(argument2)
    {}

    ~NodeBinaryExpression() {
        --unique_id;
    }

    void Calculate() override {
        static_assert(std::is_same_v<decltype(argument1_), const T> &&
                      std::is_same_v<decltype(argument2_), const T>,
                      "Arguments have to be the same type as in lambda function");
        
        result_ = expression_(argument1_, argument2_);
        SetResultAsCalculated();
    }
    
    inline const void* GetResult() const override {
        return &result_;
    }

private:
    const Expression expression_;
    const T argument1_;
    const T argument2_;
    
    T result_;
};

template <typename Expression, typename T>
class NodeBinaryExpressionFuture : public Node {
public:
    NodeBinaryExpressionFuture(Expression&& expression, const T& argument1, const T* argument2) :
        expression_(std::move(expression)),
        argument1_(argument1),
        argument2_(argument2)
    {}

    ~NodeBinaryExpressionFuture() {
        --unique_id;
    }

    void Calculate() override {
        static_assert(std::is_same_v<decltype(argument1_), const T> &&
                      std::is_same_v<decltype(argument2_), const T*>,
                      "Arguments have to be the same type as in lambda function");
        
        result_ = expression_(argument1_, *argument2_);
        SetResultAsCalculated();
    }
    
    inline const void* GetResult() const override {
        return &result_;
    }

private:
    const Expression expression_;
    const T argument1_;
    const T* argument2_;

    T result_;
};

template <typename Expression, typename T>
class NodeBinaryExpressionTwoFuture : public Node {
public:
    NodeBinaryExpressionTwoFuture(Expression&& expression, const T* argument1, const T* argument2) :
        expression_(std::move(expression)),
        argument1_(argument1),
        argument2_(argument2)
    {}

    ~NodeBinaryExpressionTwoFuture() {
        --unique_id;
    }

    void Calculate() override {
        static_assert(std::is_same_v<decltype(argument1_), const T*> &&
                      std::is_same_v<decltype(argument2_), const T*>,
                      "Arguments have to be the same type as in lambda function");
        
        result_ = expression_(*argument1_, *argument2_);
        SetResultAsCalculated();
    }
    
    inline const void* GetResult() const override {
        return &result_;
    }

private:
    const Expression expression_;
    const T* argument1_;
    const T* argument2_;

    T result_;
};

template <typename Expression, typename T>
class NodeUnaryExpression : public Node {
public:
    NodeUnaryExpression(Expression&& expression, const T& argument1) :
        expression_(std::move(expression)),
        argument1_(argument1)
    {}

    ~NodeUnaryExpression() {
        --unique_id;
    }

    void Calculate() override {
        static_assert(std::is_same_v<decltype(argument1_), const T>,
                      "Argument has to be the same type as in lambda function");
        
        result_ = expression_(argument1_);
        SetResultAsCalculated();
    }
    
    inline const void* GetResult() const override {
        return &result_;
    }

private:
    const Expression expression_;
    const T argument1_;

    T result_;
};

template <typename Expression, typename T>
class NodeUnaryExpressionFuture : public Node {
public:
    NodeUnaryExpressionFuture(Expression&& expression, const T* argument1) :
        expression_(std::move(expression)),
        argument1_(argument1)
    {}

    ~NodeUnaryExpressionFuture() {
        --unique_id;
    }

    void Calculate() override {
        static_assert(std::is_same_v<decltype(argument1_), const T*>,
                      "Argument has to be the same type as in lambda function");
        
        result_ = expression_(*argument1_);
        SetResultAsCalculated();
    }
    
    inline const void* GetResult() const override {
        return &result_;
    }

private:
    const Expression expression_;
    const T* argument1_;

    T result_;
};


using NodePointer = std::shared_ptr<Node>;

template <typename Expression, typename T>
NodePointer CreateNode(Expression&& expression, const T& argument1, const T& argument2) {
    return std::make_shared<NodeBinaryExpression<Expression, T>>(std::move(expression), argument1, argument2);
}

template <typename Expression, typename T>
NodePointer CreateNode(Expression&& expression, const T& argument1, const T* argument2) {
    return std::make_shared<NodeBinaryExpressionFuture<Expression, T>>(std::move(expression), argument1, argument2);
}

template <typename Expression, typename T>
NodePointer CreateNode(Expression&& expression, const T* argument1, const T* argument2) {
    return std::make_shared<NodeBinaryExpressionTwoFuture<Expression, T>>(std::move(expression), argument1, argument2);
}

template <typename Expression, typename T>
NodePointer CreateNode(Expression&& expression, const T& argument1) {
    return std::make_shared<NodeUnaryExpression<Expression, T>>(std::move(expression), argument1);
}

template <typename Expression, typename T>
NodePointer CreateNode(Expression&& expression, const T* argument1) {
    return std::make_shared<NodeUnaryExpressionFuture<Expression, T>>(std::move(expression), argument1);
}
