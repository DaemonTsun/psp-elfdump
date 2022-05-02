
#include <algorithm>
#include <ostream>
#include "parse_instructions.hpp"

#define clear_instruction() \
    inst.opcode = 0;\
    inst.address = 0;\
    inst.mnemonic = allegrex_mnemonic::_UNKNOWN;\
    inst.arguments.clear();

#define setup_test_variables() \
    instruction inst;\
    clear_instruction();\
    parse_config conf;\
    conf.vaddr = 0;\
    conf.log = nullptr;\
    conf.emit_pseudo = false;\
    parse_data pdata;

#define emit_pseudoinstructions()\
    conf.emit_pseudo = true;
    
#define parse_opcode(OPCODE) \
    inst.opcode = OPCODE;\
    parse_instruction(OPCODE, &inst, &conf, &pdata);
    
#define assert_mnemonic(MNEM) \
    assert_equal(inst.mnemonic, allegrex_mnemonic::MNEM);
    
#define assert_argument_count(N) \
    assert_equal(inst.arguments.size(), N);
    
#define assert_argument_non_extra_count(N) \
    auto _count = std::count_if(inst.arguments.begin(), \
                                inst.arguments.end(), \
                                [](const instruction_argument &arg){ return !std::holds_alternative<extra>(arg); }\
                               ); \
    assert_equal(_count, N);
    
#define assert_argument_type(N, T) \
    assert_equal(std::holds_alternative<T>(inst.arguments.at(N)), true);

template<typename T>
void _assert_argument_equals(const instruction &inst, size_t arg, T value)
{
    assert_equal(std::get<T>(inst.arguments.at(arg)), value);
}
    
#define assert_argument_equals(N, ...) \
    assert_equal(std::get<decltype(__VA_ARGS__)>(inst.arguments.at(N)), (__VA_ARGS__));
    
#define assert_argument_vfpu_prefix_equals(N, I, X) \
    assert_equal(std::get<vfpu_prefix_array>(inst.arguments.at(N)).data[I], X);

#define assert_argument_vfpu_destination_prefix_equals(N, I, X) \
    assert_equal(std::get<vfpu_destination_prefix_array>(inst.arguments.at(N)).data[I], X);
    
#define assert_argument_vfpu_size(SZ) \
    assert_equal(get_vfpu_size(inst.opcode), vfpu_size::SZ);

std::ostream &operator<<(std::ostream &lhs, allegrex_mnemonic rhs)
{
    return lhs << get_mnemonic_name(rhs);
}

std::ostream &operator<<(std::ostream &lhs, mips_register rhs)
{
    return lhs << register_name(rhs);
}

std::ostream &operator<<(std::ostream &lhs, mips_fpu_register rhs)
{
    return lhs << register_name(rhs);
}

std::ostream &operator<<(std::ostream &lhs, vfpu_register rhs)
{
    return lhs << register_name(rhs) << size_suffix(rhs.size);
}

std::ostream &operator<<(std::ostream &lhs, vfpu_size rhs)
{
    return lhs << size_suffix(rhs);
}

std::ostream &operator<<(std::ostream &lhs, vfpu_condition rhs)
{
    return lhs << vfpu_condition_name(rhs);
}

std::ostream &operator<<(std::ostream &lhs, shift rhs)
{
    return lhs << static_cast<int>(rhs.data);
}

std::ostream &operator<<(std::ostream &lhs, extra rhs)
{
    return lhs << static_cast<int>(rhs.data);
}

std::ostream &operator<<(std::ostream &lhs, branch_address rhs)
{
    return lhs << std::hex << rhs.data;
}

std::ostream &operator<<(std::ostream &lhs, jump_address rhs)
{
    return lhs << std::hex << rhs.data;
}

std::ostream &operator<<(std::ostream &lhs, condition_code rhs)
{
    return lhs << static_cast<int>(rhs.data);
}

std::ostream &operator<<(std::ostream &lhs, bitfield_pos rhs)
{
    return lhs << "pos(" << static_cast<int>(rhs.data) << ")";
}

std::ostream &operator<<(std::ostream &lhs, bitfield_size rhs)
{
    return lhs << "size(" << static_cast<int>(rhs.data) << ")";
}

std::ostream &operator<<(std::ostream &lhs, vfpu_prefix rhs)
{
    return lhs << vfpu_prefix_name(rhs);
}

std::ostream &operator<<(std::ostream &lhs, vfpu_prefix_array rhs)
{
    return lhs << '[' << rhs.data[0]
               << ',' << rhs.data[1]
               << ',' << rhs.data[2]
               << ',' << rhs.data[3]
               << ']';
}

std::ostream &operator<<(std::ostream &lhs, vfpu_destination_prefix rhs)
{
    return lhs << vfpu_destination_prefix_name(rhs);
}

std::ostream &operator<<(std::ostream &lhs, vfpu_destination_prefix_array rhs)
{
    return lhs << '[' << rhs.data[0]
               << ',' << rhs.data[1]
               << ',' << rhs.data[2]
               << ',' << rhs.data[3]
               << ']';
}

template<typename T>
std::ostream &operator<<(std::ostream &lhs, immediate<T> rhs)
{
    return lhs << rhs.data;
}

std::ostream &operator<<(std::ostream &lhs, coprocessor_register rhs)
{
    return lhs << '[' << static_cast<int>(rhs.rd) << ", " << static_cast<int>(rhs.sel) << ']';
}

bool operator==(const shift &lhs, const shift &rhs)
{
    return lhs.data == rhs.data;
}

bool operator==(const extra &lhs, const extra &rhs)
{
    return lhs.data == rhs.data;
}

bool operator==(const branch_address &lhs, const branch_address &rhs)
{
    return lhs.data == rhs.data;
}

bool operator==(const jump_address &lhs, const jump_address &rhs)
{
    return lhs.data == rhs.data;
}

bool operator==(const condition_code &lhs, const condition_code &rhs)
{
    return lhs.data == rhs.data;
}

bool operator==(const bitfield_pos &lhs, const bitfield_pos &rhs)
{
    return lhs.data == rhs.data;
}

bool operator==(const bitfield_size &lhs, const bitfield_size &rhs)
{
    return lhs.data == rhs.data;
}

bool operator==(const coprocessor_register &lhs, const coprocessor_register &rhs)
{
    return (lhs.rd == rhs.rd) && (lhs.sel == rhs.sel);
}

template<typename T>
bool operator==(const immediate<T> &lhs, const immediate<T> &rhs)
{
    return lhs.data == rhs.data;
}

bool operator==(const vfpu_register &lhs, const vfpu_register &rhs)
{
    return (lhs.num == rhs.num) && (lhs.size == rhs.size);
}

bool operator==(const vfpu_prefix_array &lhs, const vfpu_prefix_array &rhs)
{
    for (int i = 0; i < 4; ++i)
        if (lhs.data[i] != rhs.data[i])
            return false;

    return true;
}

bool operator==(const vfpu_destination_prefix_array &lhs, const vfpu_destination_prefix_array &rhs)
{
    for (int i = 0; i < 4; ++i)
        if (lhs.data[i] != rhs.data[i])
            return false;

    return true;
}
