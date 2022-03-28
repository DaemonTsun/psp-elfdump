
#pragma once

#include "string.hpp"
#include "parse_instructions.hpp"

typedef void(*argument_parse_function_t)(u32 opcode, instruction*, const parse_config *conf);

void arg_parse_RsRtRd(u32 opcode, instruction *inst, const parse_config *conf);
void arg_parse_AdduOr(u32 opcode, instruction *inst, const parse_config *conf);
// clz, clo
void arg_parse_RsRd(u32 opcode, instruction *inst, const parse_config *conf);
void arg_parse_RsRt(u32 opcode, instruction *inst, const parse_config *conf);

// tge, tgeu etc
void arg_parse_RsRtCode(u32 opcode, instruction *inst, const parse_config *conf);
void arg_parse_RdRtShift(u32 opcode, instruction *inst, const parse_config *conf);
void arg_parse_VarShift(u32 opcode, instruction *inst, const parse_config *conf);
// jr
void arg_parse_RegJumpRs(u32 opcode, instruction *inst, const parse_config *conf);
// jalr
void arg_parse_RegJumpRdRs(u32 opcode, instruction *inst, const parse_config *conf);
void arg_parse_Syscall(u32 opcode, instruction *inst, const parse_config *conf);
void arg_parse_Sync(u32 opcode, instruction *inst, const parse_config *conf);

void arg_parse_Rs(u32 opcode, instruction *inst, const parse_config *conf);
void arg_parse_Rd(u32 opcode, instruction *inst, const parse_config *conf);
void arg_parse_RdRt(u32 opcode, instruction *inst, const parse_config *conf);

void arg_parse_Cop0RtRdSel(u32 opcode, instruction *inst, const parse_config *conf);

void arg_parse_RsImmediateU(u32 opcode, instruction *inst, const parse_config *conf);
void arg_parse_RsImmediateS(u32 opcode, instruction *inst, const parse_config *conf);
void arg_parse_RtImmediateU(u32 opcode, instruction *inst, const parse_config *conf);
void arg_parse_RsRelAddress(u32 opcode, instruction *inst, const parse_config *conf);
void arg_parse_JumpAddress(u32 opcode, instruction *inst, const parse_config *conf);

void arg_parse_RsRtRelAddress(u32 opcode, instruction *inst, const parse_config *conf);
// B pseudoinstruction
void arg_parse_Beq(u32 opcode, instruction *inst, const parse_config *conf);
// BL pseudoinstruction
void arg_parse_Beql(u32 opcode, instruction *inst, const parse_config *conf);

void arg_parse_RsRtImmediateU(u32 opcode, instruction *inst, const parse_config *conf);
void arg_parse_RsRtImmediateS(u32 opcode, instruction *inst, const parse_config *conf);
// LI pseudoinstruction
void arg_parse_Addi(u32 opcode, instruction *inst, const parse_config *conf);
void arg_parse_Ori(u32 opcode, instruction *inst, const parse_config *conf); // technically same as Addiu

// lb, lh, lw, etc...
void arg_parse_RsRtMemOffset(u32 opcode, instruction *inst, const parse_config *conf);

void arg_parse_Cache(u32 opcode, instruction *inst, const parse_config *conf);

// special3
void arg_parse_Ext(u32 opcode, instruction *inst, const parse_config *conf);
void arg_parse_Ins(u32 opcode, instruction *inst, const parse_config *conf);

// FPU
void arg_parse_FPURelAddress(u32 opcode, instruction *inst, const parse_config *conf);
void arg_parse_RsFtMemOffset(u32 opcode, instruction *inst, const parse_config *conf);
void arg_parse_FPUFtFsFd(u32 opcode, instruction *inst, const parse_config *conf);
void arg_parse_FPUFsFd(u32 opcode, instruction *inst, const parse_config *conf);
void arg_parse_FPUCompare(u32 opcode, instruction *inst, const parse_config *conf);
void arg_parse_FPURtFs(u32 opcode, instruction *inst, const parse_config *conf);

// VFPU
void arg_parse_VFPU_Cop2(u32 opcode, instruction *inst, const parse_config *conf);
void arg_parse_VFPU_MFTV(u32 opcode, instruction *inst, const parse_config *conf);

// 3op, e.g. vadd
void arg_parse_VFPU_Vd_Vs_Vt(u32 opcode, instruction *inst, const parse_config *conf);
void arg_parse_VFPU_VdSingle_Vs_Vt(u32 opcode, instruction *inst, const parse_config *conf);
void arg_parse_VFPU_Vd_Vs_VtSingle(u32 opcode, instruction *inst, const parse_config *conf);

void arg_parse_VFPU_Vcrs(u32 opcode, instruction *inst, const parse_config *conf);
void arg_parse_VFPU_Vcmp(u32 opcode, instruction *inst, const parse_config *conf);

// 2op, e.g. vmov
void arg_parse_VFPU_Vd_Vs(u32 opcode, instruction *inst, const parse_config *conf);
void arg_parse_VFPU_VdSingle_Vs(u32 opcode, instruction *inst, const parse_config *conf);

// 1op, e.g. vidt
void arg_parse_VFPU_Vd(u32 opcode, instruction *inst, const parse_config *conf);
void arg_parse_VFPU_VdSingle(u32 opcode, instruction *inst, const parse_config *conf);

void arg_parse_VFPU_VdHalf_Vs(u32 opcode, instruction *inst, const parse_config *conf);
void arg_parse_VFPU_VdDouble_Vs(u32 opcode, instruction *inst, const parse_config *conf);

void arg_parse_VFPU_Vmfvc(u32 opcode, instruction *inst, const parse_config *conf);
void arg_parse_VFPU_Vmtvc(u32 opcode, instruction *inst, const parse_config *conf);
void arg_parse_VFPU_ColorConv(u32 opcode, instruction *inst, const parse_config *conf);
void arg_parse_VFPU_Vwbn(u32 opcode, instruction *inst, const parse_config *conf);
