#pragma once

#include <memory>
#include <string>
#include <vector>

namespace clickhouse {

using TypeRef = std::shared_ptr<class Type>;

class Type {
public:
    enum Code {
        Void = 0,
        Int8,
        Int16,
        Int32,
        Int64,
        UInt8,
        UInt16,
        UInt32,
        UInt64,
        Float32,
        Float64,
        String,
        FixedString,
        DateTime,
        Date,
        Array,
        Tuple
    };

    /// Destructor
    ~Type();

    /// Type's code.
    Code GetCode() const;

    /// Type of array's elements.
    TypeRef GetItemType() const;

    /// String representation of the type.
    std::string GetName() const;

public:
    static TypeRef CreateArray(TypeRef item_type);

    static TypeRef CreateDate();

    static TypeRef CreateDateTime();

    template <typename T>
    static TypeRef CreateSimple();

    static TypeRef CreateString();

    static TypeRef CreateString(size_t n);

private:
    Type(const Code code);

    struct ArrayImpl {
        TypeRef item_type;
    };

    struct TupleImpl {
        std::vector<TypeRef> item_types;
    };


    const Code code_;
    union {
        ArrayImpl* array_;
        TupleImpl* tuple_;
        int string_size_;
    };
};

template <>
inline TypeRef Type::CreateSimple<int8_t>() {
    return TypeRef(new Type(Int8));
}

template <>
inline TypeRef Type::CreateSimple<int16_t>() {
    return TypeRef(new Type(Int16));
}

template <>
inline TypeRef Type::CreateSimple<int32_t>() {
    return TypeRef(new Type(Int32));
}

template <>
inline TypeRef Type::CreateSimple<int64_t>() {
    return TypeRef(new Type(Int64));
}

template <>
inline TypeRef Type::CreateSimple<uint8_t>() {
    return TypeRef(new Type(UInt8));
}

template <>
inline TypeRef Type::CreateSimple<uint16_t>() {
    return TypeRef(new Type(UInt16));
}

template <>
inline TypeRef Type::CreateSimple<uint32_t>() {
    return TypeRef(new Type(UInt32));
}

template <>
inline TypeRef Type::CreateSimple<uint64_t>() {
    return TypeRef(new Type(UInt64));
}

template <>
inline TypeRef Type::CreateSimple<float>() {
    return TypeRef(new Type(Float32));
}

template <>
inline TypeRef Type::CreateSimple<double>() {
    return TypeRef(new Type(Float64));
}

}
