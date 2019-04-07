#include <cstring>
#include "ee_jittrans.hpp"
#include "emotioninterpreter.hpp"
#include "../errors.hpp"

void EE_JitTranslator::reset_instr_info()
{
    //TODO
}

IR::Block EE_JitTranslator::translate(EmotionEngine &ee, uint32_t pc)
{
    //TODO
    IR::Block block;
    std::vector<IR::Instruction> instrs;

    bool branch_op = false;
    bool branch_delayslot = false;
    int cycle_count = 0;

    while (!branch_delayslot)
    {
        translate_op(instrs, ee.read32(pc));

        if (branch_op)
            branch_delayslot = true;

        branch_op = is_branch(ee.read32(pc));

        pc += 4;
        ++cycle_count;
    }

    for (auto instr : instrs)
        block.add_instr(instr);
    
    block.set_cycle_count(cycle_count);
    
    return block;
}

void EE_JitTranslator::translate_op(std::vector<IR::Instruction>& instrs, uint32_t opcode) const
{
    if (!opcode)
        return; // op is effective nop

    uint8_t op = opcode >> 26;
    IR::Instruction instr;

    switch (op)
    {
        case 0x00:
            // Special Operation
            translate_op_special(instrs, opcode);
            return;
        case 0x01:
            // Regimm Operation
            translate_op_regimm(instrs, opcode);
            return;
        case 0x02:
            // J
            Errors::print_warning("[EE_JIT] Unrecognized op J\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x03:
            // JAL
            Errors::print_warning("[EE_JIT] Unrecognized op JAL\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x04:
            // BEQ
            Errors::print_warning("[EE_JIT] Unrecognized op BEQ\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x05:
            // BNE
            Errors::print_warning("[EE_JIT] Unrecognized op BNE\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x06:
            // BLEZ
            Errors::print_warning("[EE_JIT] Unrecognized op BLEZ\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x07:
            // BGTZ
            Errors::print_warning("[EE_JIT] Unrecognized op BGTZ\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x08:
            // ADDI
            Errors::print_warning("[EE_JIT] Unrecognized op ADDI\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x09:
            // ADDIU
            Errors::print_warning("[EE_JIT] Unrecognized op ADDIU\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x0A:
            // SLTI
            Errors::print_warning("[EE_JIT] Unrecognized op SLTI\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x0B:
            // SLTIU
            Errors::print_warning("[EE_JIT] Unrecognized op SLTIU\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x0C:
            // ANDI
            Errors::print_warning("[EE_JIT] Unrecognized op ANDI\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x0D:
            // ORI
            Errors::print_warning("[EE_JIT] Unrecognized op ORI\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x0E:
            // XORI
            Errors::print_warning("[EE_JIT] Unrecognized op XORI\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x0F:
            // LUI
            Errors::print_warning("[EE_JIT] Unrecognized op LUI\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x10:
            // COP0 (System Coprocessor)
            translate_op_cop0(instrs, opcode);
            return;
        case 0x11:
            // COP1 (Floating Point Unit)
            translate_op_cop1(instrs, opcode);
            return;
        case 0x12:
            // COP2 (Vector Unit 0)
            translate_op_cop2(instrs, opcode);
            return;
        case 0x13:
            // COP3 (unimplemented)
            Errors::die("[EE_JIT] Unrecognized cop3 opcode $%08X", opcode);
            return;
        case 0x14:
            // BEQL
            Errors::print_warning("[EE_JIT] Unrecognized op BEQL\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x15:
            // BNEL
            Errors::print_warning("[EE_JIT] Unrecognized op BNEL\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x16:
            // BLEZL
            Errors::print_warning("[EE_JIT] Unrecognized op BLEZL\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x17:
            // BGTZL
            Errors::print_warning("[EE_JIT] Unrecognized op BGTZL\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x18:
            // DADDI
            Errors::print_warning("[EE_JIT] Unrecognized op DADDI\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x19:
            // DADDIU
            Errors::print_warning("[EE_JIT] Unrecognized op DADDIU\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x1A:
            // LDL
            Errors::print_warning("[EE_JIT] Unrecognized op LDL\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x1B:
            // LDR
            Errors::print_warning("[EE_JIT] Unrecognized op LDR\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x1C:
            // MMI Operation
            translate_op_mmi(instrs, opcode);
            return;
        case 0x1E:
            // LQ
            Errors::print_warning("[EE_JIT] Unrecognized op LQ\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x1F:
            // SQ
            Errors::print_warning("[EE_JIT] Unrecognized op SQ\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x20:
            // LB
            Errors::print_warning("[EE_JIT] Unrecognized op LB\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x21:
            // LH
            Errors::print_warning("[EE_JIT] Unrecognized op LH\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x22:
            // LWL
            Errors::print_warning("[EE_JIT] Unrecognized op LWL\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x23:
            // LW
            Errors::print_warning("[EE_JIT] Unrecognized op LW\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x24:
            // LBU
            Errors::print_warning("[EE_JIT] Unrecognized op LBU\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x25:
            // LHU
            Errors::print_warning("[EE_JIT] Unrecognized op LHU\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x26:
            // LWR
            Errors::print_warning("[EE_JIT] Unrecognized op LWR\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x27:
            // LWU
            Errors::print_warning("[EE_JIT] Unrecognized op LWU\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x28:
            // SB
            Errors::print_warning("[EE_JIT] Unrecognized op SB\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x29:
            // SH
            Errors::print_warning("[EE_JIT] Unrecognized op SH\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x2A:
            // SWL
            Errors::print_warning("[EE_JIT] Unrecognized op SWL\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x2B:
            // SW
            Errors::print_warning("[EE_JIT] Unrecognized op SW\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x2C:
            // SDL
            Errors::print_warning("[EE_JIT] Unrecognized op SDL\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x2D:
            // SDR
            Errors::print_warning("[EE_JIT] Unrecognized op SDR\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x2E:
            // SWR
            Errors::print_warning("[EE_JIT] Unrecognized op SWR\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x2F:
            // CACHE
            Errors::print_warning("[EE_JIT] Unrecognized op CACHE\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x31:
            // LWC1
            Errors::print_warning("[EE_JIT] Unrecognized op LWC1\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x33:
            // PREFETCH
            return;
        case 0x36:
            // LQC2
            Errors::print_warning("[EE_JIT] Unrecognized op LQC2\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x37:
            // LD
            Errors::print_warning("[EE_JIT] Unrecognized op LD\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x39:
            // SWC1
            Errors::print_warning("[EE_JIT] Unrecognized op SWC1\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x3E:
            // SQC2
            Errors::print_warning("[EE_JIT] Unrecognized op SQC2\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x3F:
            // SD
            Errors::print_warning("[EE_JIT] Unrecognized op SD\n", op);
            fallback_interpreter(instr, opcode);
            break;
        default:
            Errors::die("[EE_JIT] Unrecognized op $%02X", op);
            return;
    }
    instrs.push_back(instr);
}

void EE_JitTranslator::translate_op_special(std::vector<IR::Instruction>& instrs, uint32_t opcode) const
{
    uint8_t op = opcode & 0x3F;
    IR::Instruction instr;

    switch (op)
    {
        case 0x00:
            // SLL
            Errors::print_warning("[EE_JIT] Unrecognized special op SLL\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x02:
            // SRL
            Errors::print_warning("[EE_JIT] Unrecognized special op SRL\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x03:
            // SRA
            Errors::print_warning("[EE_JIT] Unrecognized special op SRA\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x04:
            // SLLV
            Errors::print_warning("[EE_JIT] Unrecognized special op SLLV\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x06:
            // SRLV
            Errors::print_warning("[EE_JIT] Unrecognized special op SRLV\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x07:
            // SRAV
            Errors::print_warning("[EE_JIT] Unrecognized special op SRAV\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x08:
            // JR
            Errors::print_warning("[EE_JIT] Unrecognized special op JR\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x09:
            // JALR
            Errors::print_warning("[EE_JIT] Unrecognized special op JALR\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x0A:
            // MOVZ
            Errors::print_warning("[EE_JIT] Unrecognized special op MOVZ\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x0B:
            // MOVN
            Errors::print_warning("[EE_JIT] Unrecognized special op MOVN\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x0C:
            // SYSCALL
            Errors::print_warning("[EE_JIT] Unrecognized special op SYSCALL\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x0D:
            // BREAK
            Errors::print_warning("[EE_JIT] Unrecognized special op BREAK\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x10:
            // MFHI
            Errors::print_warning("[EE_JIT] Unrecognized special op MFHI\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x11:
            // MTHI
            Errors::print_warning("[EE_JIT] Unrecognized special op MTHI\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x12:
            // MFLO
            Errors::print_warning("[EE_JIT] Unrecognized special op MFLO\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x13:
            // MTLO
            Errors::print_warning("[EE_JIT] Unrecognized special op MTLO\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x14:
            // DSLLV
            Errors::print_warning("[EE_JIT] Unrecognized special op DSLLV\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x16:
            // DSRLV
            Errors::print_warning("[EE_JIT] Unrecognized special op DSRLV\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x17:
            // DSRAV
            Errors::print_warning("[EE_JIT] Unrecognized special op DSRAV\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x18:
            // MULT
            Errors::print_warning("[EE_JIT] Unrecognized special op MULT\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x19:
            // MULTU
            Errors::print_warning("[EE_JIT] Unrecognized special op MULTU\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x1A:
            // DIV
            Errors::print_warning("[EE_JIT] Unrecognized special op DIV\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x1B:
            // DIVU
            Errors::print_warning("[EE_JIT] Unrecognized special op DIVU\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x20:
            // ADD
            Errors::print_warning("[EE_JIT] Unrecognized special op ADD\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x21:
            // ADDU
            Errors::print_warning("[EE_JIT] Unrecognized special op ADDU\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x22:
            // SUB
            Errors::print_warning("[EE_JIT] Unrecognized special op SUB\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x23:
            // SUBU
            Errors::print_warning("[EE_JIT] Unrecognized special op SUBU\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x24:
            // AND
            Errors::print_warning("[EE_JIT] Unrecognized special op AND\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x25:
            // OR
            Errors::print_warning("[EE_JIT] Unrecognized special op OR\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x26:
            // XOR
            Errors::print_warning("[EE_JIT] Unrecognized special op XOR\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x27:
            // NOR
            Errors::print_warning("[EE_JIT] Unrecognized special op NOR\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x28:
            // MFSA
            Errors::print_warning("[EE_JIT] Unrecognized special op MFSA\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x29:
            // MTSA
            Errors::print_warning("[EE_JIT] Unrecognized special op MTSA\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x2A:
            // SLT
            Errors::print_warning("[EE_JIT] Unrecognized special op SLT\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x2B:
            // SLTU
            Errors::print_warning("[EE_JIT] Unrecognized special op SLTU\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x2C:
            // DADD
            Errors::print_warning("[EE_JIT] Unrecognized special op DADD\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x2D:
            // DADDU
            Errors::print_warning("[EE_JIT] Unrecognized special op DADDU\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x2E:
            // DSUB
            Errors::print_warning("[EE_JIT] Unrecognized special op DSUB\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x2F:
            // DSUBU
            Errors::print_warning("[EE_JIT] Unrecognized special op DSUBU\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x34:
            // TEQ
            Errors::print_warning("[EE_JIT] Unrecognized special op TEQ\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x38:
            // DSLL
            Errors::print_warning("[EE_JIT] Unrecognized special op DSLL\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x3A:
            // DSRL
            Errors::print_warning("[EE_JIT] Unrecognized special op DSRL\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x3B:
            // DSRA
            Errors::print_warning("[EE_JIT] Unrecognized special op DSRA\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x3C:
            // DSLL32
            Errors::print_warning("[EE_JIT] Unrecognized special op DSLL32\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x3E:
            // DSRL32
            Errors::print_warning("[EE_JIT] Unrecognized special op DSRL32\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x3F:
            // DSRA32
            Errors::print_warning("[EE_JIT] Unrecognized special op DSRA32\n", op);
            fallback_interpreter(instr, opcode);
            break;
        default:
            Errors::die("[EE_JIT] Unrecognized special op $%02X", op);
            return;
    }
    instrs.push_back(instr);
}

void EE_JitTranslator::translate_op_regimm(std::vector<IR::Instruction>& instrs, uint32_t opcode) const
{
    uint8_t op = (opcode >> 16) & 0x1F;
    IR::Instruction instr;

    switch (op)
    {
        case 0x00:
            // BLTZ
            Errors::print_warning("[EE_JIT] Unrecognized regimm op BLTZ\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x01:
            // BGEZ
            Errors::print_warning("[EE_JIT] Unrecognized regimm op BGEZ\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x02:
            // BLTZL
            Errors::print_warning("[EE_JIT] Unrecognized regimm op BLTZL\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x03:
            // BGEZL
            Errors::print_warning("[EE_JIT] Unrecognized regimm op BGEZL\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x10:
            // BLTZAL
            Errors::print_warning("[EE_JIT] Unrecognized regimm op BLTZAL\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x11:
            // BGEZAL
            Errors::print_warning("[EE_JIT] Unrecognized regimm op BGEZAL\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x12:
            // BLTZALL
            Errors::print_warning("[EE_JIT] Unrecognized regimm op BLTZALL\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x13:
            // BGEZALL
            Errors::print_warning("[EE_JIT] Unrecognized regimm op BGEZALL\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x18:
            // MTSAB
            Errors::print_warning("[EE_JIT] Unrecognized regimm op MTSAB\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x19:
            // MTASH
            Errors::print_warning("[EE_JIT] Unrecognized regimm op MTSAH\n", op);
            fallback_interpreter(instr, opcode);
            break;
        default:
            Errors::die("[EE_JIT] Unrecognized regimm op $%02X", op);
            return;
    }
    instrs.push_back(instr);
}

void EE_JitTranslator::translate_op_mmi(std::vector<IR::Instruction>& instrs, uint32_t opcode) const
{
    uint8_t op = opcode & 0x3F;
    IR::Instruction instr;

    switch (op)
    {
        case 0x00:
            // MADD
            Errors::print_warning("[EE_JIT] Unrecognized mmi op MADD\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x01:
            // MADDU
            Errors::print_warning("[EE_JIT] Unrecognized mmi op MADDU\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x04:
            // PLZCW
            Errors::print_warning("[EE_JIT] Unrecognized mmi op PLZCW\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x08:
            // MMI0 Operation
            translate_op_mmi0(instrs, opcode);
            return;
        case 0x09:
            // MMI2 Operation
            translate_op_mmi2(instrs, opcode);
            return;
        case 0x10:
            // MFHI1
            Errors::print_warning("[EE_JIT] Unrecognized mmi op MFHI1\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x11:
            // MTHI1
            Errors::print_warning("[EE_JIT] Unrecognized mmi op MTHI1\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x12:
            // MFLO1
            Errors::print_warning("[EE_JIT] Unrecognized mmi op MFLO1\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x13:
            // MTLO1
            Errors::print_warning("[EE_JIT] Unrecognized mmi op MTLO1\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x18:
            // MULT1
            Errors::print_warning("[EE_JIT] Unrecognized mmi op MULT1\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x19:
            // MULTU1
            Errors::print_warning("[EE_JIT] Unrecognized mmi op MULTU1\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x1A:
            // DIV1
            Errors::print_warning("[EE_JIT] Unrecognized mmi op DIV1\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x1B:
            // DIVU1
            Errors::print_warning("[EE_JIT] Unrecognized mmi op DIVU1\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x20:
            // MADD1
            Errors::print_warning("[EE_JIT] Unrecognized mmi op MADD1\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x21:
            // MADDU1
            Errors::print_warning("[EE_JIT] Unrecognized mmi op MADDU1\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x28:
            // MMI1 Operation
            translate_op_mmi1(instrs, opcode);
            return;
        case 0x29:
            // MMI3 Operation
            translate_op_mmi3(instrs, opcode);
            return;
        case 0x30:
            // PMFHLFMT
            Errors::print_warning("[EE_JIT] Unrecognized mmi op PMFHLFMT\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x31:
            // PMTHLLW
            Errors::print_warning("[EE_JIT] Unrecognized mmi op PMTHLLW\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x34:
            // PSLLH
            Errors::print_warning("[EE_JIT] Unrecognized mmi op PSLLH\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x36:
            // PSRLH
            Errors::print_warning("[EE_JIT] Unrecognized mmi op PSRLH\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x37:
            // PSRAH
            Errors::print_warning("[EE_JIT] Unrecognized mmi op PSRAH\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x3C:
            // PSLLW
            Errors::print_warning("[EE_JIT] Unrecognized mmi op PSLLW\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x3E:
            // PSRLW
            Errors::print_warning("[EE_JIT] Unrecognized mmi op PSRLW\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x3F:
            // PSRAW
            Errors::print_warning("[EE_JIT] Unrecognized mmi op PSRAW\n", op);
            fallback_interpreter(instr, opcode);
            break;
        default:
            Errors::die("[EE_JIT] Unrecognized mmi op $%02X", op);
            return;
    }
    instrs.push_back(instr);
}

void EE_JitTranslator::translate_op_mmi0(std::vector<IR::Instruction>& instrs, uint32_t opcode) const
{
    uint8_t op = (opcode >> 6) & 0x1F;
    IR::Instruction instr;

    switch (op)
    {
        case 0x00:
            // PADDW
            Errors::print_warning("[EE_JIT] Unrecognized mmi0 op PADDW\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x01:
            // PSUBW
            Errors::print_warning("[EE_JIT] Unrecognized mmi0 op PSUBW\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x02:
            // PCGTW
            Errors::print_warning("[EE_JIT] Unrecognized mmi0 op PCTGW\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x03:
            // PMAXW
            Errors::print_warning("[EE_JIT] Unrecognized mmi0 op PMAXW\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x04:
            // PADDH
            Errors::print_warning("[EE_JIT] Unrecognized mmi0 op PADDH\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x05:
            // PSUBH
            Errors::print_warning("[EE_JIT] Unrecognized mmi0 op PSUBH\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x06:
            // PCTGH
            Errors::print_warning("[EE_JIT] Unrecognized mmi0 op PCTGH\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x07:
            // PMAXH
            Errors::print_warning("[EE_JIT] Unrecognized mmi0 op PMAXH\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x08:
            // PADDB
            Errors::print_warning("[EE_JIT] Unrecognized mmi0 op PADDB\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x09:
            // PSUBB
            Errors::print_warning("[EE_JIT] Unrecognized mmi0 op PSUBB\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x0A:
            // PCTGB
            Errors::print_warning("[EE_JIT] Unrecognized mmi0 op PCTGB\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x10:
            // PADDSW
            Errors::print_warning("[EE_JIT] Unrecognized mmi0 op PADDSW\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x11:
            // PSUBSW
            Errors::print_warning("[EE_JIT] Unrecognized mmi0 op PSUBSW\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x12:
            // PADDW
            Errors::print_warning("[EE_JIT] Unrecognized mmi0 op PADDW\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x13:
            // PPACW
            Errors::print_warning("[EE_JIT] Unrecognized mmi0 op PPACW\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x14:
            // PADDSH
            Errors::print_warning("[EE_JIT] Unrecognized mmi0 op PADDSH\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x15:
            // PSUBSH
            Errors::print_warning("[EE_JIT] Unrecognized mmi0 op PSUBSH\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x16:
            // PEXTLH
            Errors::print_warning("[EE_JIT] Unrecognized mmi0 op PEXTLH\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x17:
            // PPACH
            Errors::print_warning("[EE_JIT] Unrecognized mmi0 op PPACH\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x18:
            // PADDSB
            Errors::print_warning("[EE_JIT] Unrecognized mmi0 op PADDSB\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x19:
            // PSUBSB
            Errors::print_warning("[EE_JIT] Unrecognized mmi0 op PSUBSB\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x1A:
            // PEXTLB
            Errors::print_warning("[EE_JIT] Unrecognized mmi0 op PADDW\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x1B:
            // PPACB
            Errors::print_warning("[EE_JIT] Unrecognized mmi0 op PPACB\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x1E:
            // PEXT5
            Errors::print_warning("[EE_JIT] Unrecognized mmi0 op PEXT5\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x1F:
            // PPAC5
            Errors::print_warning("[EE_JIT] Unrecognized mmi0 op PPAC5\n", op);
            fallback_interpreter(instr, opcode);
            break;
        default:
            Errors::die("[EE_JIT] Unrecognized mmi0 op $%02X", op);
            return;
    }
    instrs.push_back(instr);
}

void EE_JitTranslator::translate_op_mmi1(std::vector<IR::Instruction>& instrs, uint32_t opcode) const
{
    uint8_t op = (opcode >> 6) & 0x1F;
    IR::Instruction instr;

    switch (op)
    {
        case 0x01:
            // PABSW
            Errors::print_warning("[EE_JIT] Unrecognized mmi1 op PABSW\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x02:
            // PCEQW
            Errors::print_warning("[EE_JIT] Unrecognized mmi1 op PABSW\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x03:
            // PMINW
            Errors::print_warning("[EE_JIT] Unrecognized mmi1 op PABSW\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x04:
            // PADSBH
            Errors::print_warning("[EE_JIT] Unrecognized mmi1 op PABSW\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x05:
            // PABSH
            Errors::print_warning("[EE_JIT] Unrecognized mmi1 op PABSW\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x06:
            // PCEQH
            Errors::print_warning("[EE_JIT] Unrecognized mmi1 op PCEQH\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x07:
            // PMINH
            Errors::print_warning("[EE_JIT] Unrecognized mmi1 op PMINH\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x0A:
            // PCEQB
            Errors::print_warning("[EE_JIT] Unrecognized mmi1 op PCEQB\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x10:
            // PADDUW
            Errors::print_warning("[EE_JIT] Unrecognized mmi1 op PADDUW\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x11:
            // PSUBUW
            Errors::print_warning("[EE_JIT] Unrecognized mmi1 op PCEQH\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x12:
            // PEXTUW
            Errors::print_warning("[EE_JIT] Unrecognized mmi1 op PEXTUW\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x14:
            // PADDUH
            Errors::print_warning("[EE_JIT] Unrecognized mmi1 op PADDUH\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x15:
            // PSUBUH
            Errors::print_warning("[EE_JIT] Unrecognized mmi1 op PCEQH\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x16:
            // PEXTUH
            Errors::print_warning("[EE_JIT] Unrecognized mmi1 op PEXTUH\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x18:
            // PADDUB
            Errors::print_warning("[EE_JIT] Unrecognized mmi1 op PADDUB\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x19:
            // PSUBUB
            Errors::print_warning("[EE_JIT] Unrecognized mmi1 op PSUBUB\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x1A:
            // PEXTUB
            Errors::print_warning("[EE_JIT] Unrecognized mmi1 op PEXTUB\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x1B:
            // QFSRV
            Errors::print_warning("[EE_JIT] Unrecognized mmi1 op QFSRV\n", op);
            fallback_interpreter(instr, opcode);
            break;
        default:
            Errors::die("[EE_JIT] Unrecognized mmi1 op $%02X", op);
            return;
    }
    instrs.push_back(instr);
}

void EE_JitTranslator::translate_op_mmi2(std::vector<IR::Instruction>& instrs, uint32_t opcode) const
{
    uint8_t op = (opcode >> 6) & 0x1F;
    IR::Instruction instr;

    switch (op)
    {
        case 0x00:
            // PMADDW
            Errors::print_warning("[EE_JIT] Unrecognized mmi2 op PMADDW\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x02:
            // PSLLVW
            Errors::print_warning("[EE_JIT] Unrecognized mmi2 op PSLLVW\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x03:
            // PSRLVW
            Errors::print_warning("[EE_JIT] Unrecognized mmi2 op PSRLVW\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x04:
            // PMSUBW
            Errors::print_warning("[EE_JIT] Unrecognized mmi2 op PMSUBW\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x08:
            // PMFHI
            Errors::print_warning("[EE_JIT] Unrecognized mmi2 op PMADDW\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x09:
            // PMFLO
            Errors::print_warning("[EE_JIT] Unrecognized mmi2 op PMFLO\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x0A:
            // PINTH
            Errors::print_warning("[EE_JIT] Unrecognized mmi2 op PINTH\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x0C:
            // PMULTW
            Errors::print_warning("[EE_JIT] Unrecognized mmi2 op PMULTW\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x0D:
            // PDIVW
            Errors::print_warning("[EE_JIT] Unrecognized mmi2 op PDIVW\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x0E:
            // PCPYLD
            Errors::print_warning("[EE_JIT] Unrecognized mmi2 op PCPYLD\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x10:
            // PMADDH
            Errors::print_warning("[EE_JIT] Unrecognized mmi2 op PMADDH\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x11:
            // PHMADH
            Errors::print_warning("[EE_JIT] Unrecognized mmi2 op PHMADH\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x12:
            // PAND
            Errors::print_warning("[EE_JIT] Unrecognized mmi2 op PAND\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x13:
            // PXOR
            Errors::print_warning("[EE_JIT] Unrecognized mmi2 op PXOR\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x14:
            // PMSUBH
            Errors::print_warning("[EE_JIT] Unrecognized mmi2 op PMSUBH\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x15:
            // PHMSBH
            Errors::print_warning("[EE_JIT] Unrecognized mmi2 op PMADDW\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x1A:
            // PEXEH
            Errors::print_warning("[EE_JIT] Unrecognized mmi2 op PEXEH\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x1B:
            // PREVW
            Errors::print_warning("[EE_JIT] Unrecognized mmi2 op PREVW\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x1C:
            // PMULTH
            Errors::print_warning("[EE_JIT] Unrecognized mmi2 op PMULTH\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x1D:
            // PDIVBW
            Errors::print_warning("[EE_JIT] Unrecognized mmi2 op PDIVBW\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x1E:
            // PEXEW
            Errors::print_warning("[EE_JIT] Unrecognized mmi2 op PEXEW\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x1F:
            // PROT3W
            Errors::print_warning("[EE_JIT] Unrecognized mmi2 op PROT3W\n", op);
            fallback_interpreter(instr, opcode);
            break;
        default:
            Errors::die("[EE_JIT] Unrecognized mmi2 op $%02X", op);
            return;
    }
    instrs.push_back(instr);
}

void EE_JitTranslator::translate_op_mmi3(std::vector<IR::Instruction>& instrs, uint32_t opcode) const
{
    uint8_t op = (opcode >> 6) & 0x1F;
    IR::Instruction instr;

    switch (op)
    {
        case 0x00:
            // PMADDUW
            Errors::print_warning("[EE_JIT] Unrecognized mmi3 op PMADDUW\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x03:
            // PSRAVW
            Errors::print_warning("[EE_JIT] Unrecognized mmi3 op PSRAVW\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x08:
            // PMTHI
            Errors::print_warning("[EE_JIT] Unrecognized mmi3 op PMTHI\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x09:
            // PMTLO
            Errors::print_warning("[EE_JIT] Unrecognized mmi3 op PMTLO\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x0A:
            // PINTEH
            Errors::print_warning("[EE_JIT] Unrecognized mmi3 op PINTEH\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x0C:
            // PMULTUW
            Errors::print_warning("[EE_JIT] Unrecognized mmi3 op PMULTUW\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x0D:
            // PDIVUW
            Errors::print_warning("[EE_JIT] Unrecognized mmi3 op PDIVUW\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x0E:
            // PCPYUD
            Errors::print_warning("[EE_JIT] Unrecognized mmi3 op PCPYUD\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x12:
            // POR
            Errors::print_warning("[EE_JIT] Unrecognized mmi3 op POR\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x13:
            // PNOR
            Errors::print_warning("[EE_JIT] Unrecognized mmi3 op PNOR\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x1A:
            // PEXCH
            Errors::print_warning("[EE_JIT] Unrecognized mmi3 op PEXCH\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x1B:
            // PCPYH
            Errors::print_warning("[EE_JIT] Unrecognized mmi3 op PCYPH\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x1E:
            // PEXCW
            Errors::print_warning("[EE_JIT] Unrecognized mmi3 op PEXCW\n", op);
            fallback_interpreter(instr, opcode);
            break;
        default:
            Errors::die("[EE_JIT] Unrecognized mmi3 op $%02X", op);
            return;
    }
    instrs.push_back(instr);
}

void EE_JitTranslator::translate_op_cop0(std::vector<IR::Instruction>& instrs, uint32_t opcode) const
{
    uint8_t op = (opcode >> 21) & 0x1F;
    IR::Instruction instr;

    switch (op)
    {
        case 0x00:
            // MFC0
            Errors::print_warning("[EE_JIT] Unrecognized cop0 op MFC0\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x04:
            // MTC0
            Errors::print_warning("[EE_JIT] Unrecognized cop0 op MTC0\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x08:
            // BC0
            Errors::print_warning("[EE_JIT] Unrecognized cop0 op BC0\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x10:
            // Type2 op
            translate_op_cop0_type2(instrs, opcode);
            return;
        default:
            Errors::die("[EE_JIT] Unrecognized cop0 op $%02X", op);
            return;
    }
    instrs.push_back(instr);
}

void EE_JitTranslator::translate_op_cop0_type2(std::vector<IR::Instruction>& instrs, uint32_t opcode) const
{
    uint8_t op = opcode & 0x3F;
    IR::Instruction instr;

    switch (op)
    {
        case 0x18:
            // ERET
            Errors::print_warning("[EE_JIT] Unrecognized cop0 type2 op ERET\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x38:
            // EI
            Errors::print_warning("[EE_JIT] Unrecognized cop0 type2 op EI\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x39:
            // DI
            Errors::print_warning("[EE_JIT] Unrecognized cop0 type2 op DI\n", op);
            fallback_interpreter(instr, opcode);
            break;
        default:
            Errors::die("[EE_JIT] Unrecognized cop0 type2 op $%02X", op);
            return;
    }
    instrs.push_back(instr);
}

void EE_JitTranslator::translate_op_cop1(std::vector<IR::Instruction>& instrs, uint32_t opcode) const
{
    uint8_t op = (opcode >> 21) & 0x1F;
    IR::Instruction instr;

    switch (op)
    {
        case 0x00:
            // MFC1
            Errors::print_warning("[EE_JIT] Unrecognized cop1 op MFC1\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x02:
            // CFC1
            Errors::print_warning("[EE_JIT] Unrecognized cop1 op CFC1\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x04:
            // MTC1
            Errors::print_warning("[EE_JIT] Unrecognized cop1 op MTC1\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x06:
            // CTC1
            Errors::print_warning("[EE_JIT] Unrecognized cop1 op CTC1\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x08:
            // BC1
            Errors::print_warning("[EE_JIT] Unrecognized cop1 op BC1\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x10:
            // FPU Operation
            translate_op_cop1_fpu(instrs, opcode);
            return;
        case 0x14:
            // CVT.S.W
            Errors::print_warning("[EE_JIT] Unrecognized cop1 op CVT.S.W\n", op);
            fallback_interpreter(instr, opcode);
            break;
        default:
            Errors::die("[EE_JIT] Unrecognized cop1 op $%02X", op);
            return;
    }
    instrs.push_back(instr);
}

void EE_JitTranslator::translate_op_cop1_fpu(std::vector<IR::Instruction>& instrs, uint32_t opcode) const
{
    uint8_t op = opcode & 0x3F;
    IR::Instruction instr;

    switch (op)
    {
        case 0x00:
            // ADD.S
            Errors::print_warning("[EE_JIT] Unrecognized fpu op ADD.S\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x01:
            // SUB.S
            Errors::print_warning("[EE_JIT] Unrecognized fpu op SUB.S\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x02:
            // MUL.S
            Errors::print_warning("[EE_JIT] Unrecognized fpu op MUL.S\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x03:
            // DIV.S
            Errors::print_warning("[EE_JIT] Unrecognized fpu op DIV.S\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x04:
            // SQRT.S
            Errors::print_warning("[EE_JIT] Unrecognized fpu op SQRT.S\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x05:
            // ABS.S
            Errors::print_warning("[EE_JIT] Unrecognized fpu op ABS.S\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x06:
            // MOV.S
            Errors::print_warning("[EE_JIT] Unrecognized fpu op MOV.S\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x07:
            // NEG.S
            Errors::print_warning("[EE_JIT] Unrecognized fpu op NEG.S\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x16:
            // RSQRT.S
            Errors::print_warning("[EE_JIT] Unrecognized fpu op RSQRT.S\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x18:
            // ADDA.S
            Errors::print_warning("[EE_JIT] Unrecognized fpu op ADDA.S\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x19:
            // SUBA.S
            Errors::print_warning("[EE_JIT] Unrecognized fpu op SUBA.S\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x1A:
            // MULA.S
            Errors::print_warning("[EE_JIT] Unrecognized fpu op MULA.S\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x1C:
            // MADD.S
            Errors::print_warning("[EE_JIT] Unrecognized fpu op MADD.S\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x1D:
            // MSUB.S
            Errors::print_warning("[EE_JIT] Unrecognized fpu op MSUB.S\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x1E:
            // MADDA.S
            Errors::print_warning("[EE_JIT] Unrecognized fpu op MADDA.S\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x1F:
            // MSUBA.S
            Errors::print_warning("[EE_JIT] Unrecognized fpu op MSUBA.S\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x24:
            // CVT.W.S
            Errors::print_warning("[EE_JIT] Unrecognized fpu op CVT.W.S\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x28:
            // MAX.S
            Errors::print_warning("[EE_JIT] Unrecognized fpu op MAX.S\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x29:
            // MIN.S
            Errors::print_warning("[EE_JIT] Unrecognized fpu op MIN.S\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x30:
            // C.F.S
            Errors::print_warning("[EE_JIT] Unrecognized fpu op C.F.S\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x32:
            // C.EQ.S
            Errors::print_warning("[EE_JIT] Unrecognized fpu op C.EQ.S\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x34:
            // C.LT.S
            Errors::print_warning("[EE_JIT] Unrecognized fpu op C.LT.S\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x36:
            // C.LE.S
            Errors::print_warning("[EE_JIT] Unrecognized fpu op C.LE.S\n", op);
            fallback_interpreter(instr, opcode);
            break;
        default:
            Errors::die("[EE_JIT] Unrecognized fpu op $%02X", op);
            return;
    }
    instrs.push_back(instr);
}

void EE_JitTranslator::translate_op_cop2(std::vector<IR::Instruction>& instrs, uint32_t opcode) const
{
    uint8_t op = (opcode >> 21) & 0x1F;
    IR::Instruction instr;

    switch (op)
    {
        case 0x01:
            // QMFC2
            Errors::print_warning("[EE_JIT] Unrecognized cop2 op QMFC2\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x02:
            // CFC2
            Errors::print_warning("[EE_JIT] Unrecognized cop2 op CFC2\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x05:
            // QMTC2
            Errors::print_warning("[EE_JIT] Unrecognized cop2 op QMTC2\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x06:
            // CTC2
            Errors::print_warning("[EE_JIT] Unrecognized cop2 op CTC2\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x08:
            // BC2
            Errors::print_warning("[EE_JIT] Unrecognized cop2 op BC2\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x10:
        case 0x11:
        case 0x12:
        case 0x13:
        case 0x14:
        case 0x15:
        case 0x16:
        case 0x17:
        case 0x18:
        case 0x19:
        case 0x1A:
        case 0x1B:
        case 0x1C:
        case 0x1D:
        case 0x1E:
        case 0x1F:
            // COP2 Special Operation
            translate_op_cop2_special(instrs, opcode);
            return;
        default:
            Errors::die("[EE_JIT] Unrecognized cop2 op $%02X", op);
            return;
    }
    instrs.push_back(instr);
}

void EE_JitTranslator::translate_op_cop2_special(std::vector<IR::Instruction>& instrs, uint32_t opcode) const
{
    uint8_t op = opcode & 0x3F;
    IR::Instruction instr;

    switch (op)
    {
        case 0x00:
        case 0x01:
        case 0x02:
        case 0x03:
            // VADDBC
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special op VADDBC\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x04:
        case 0x05:
        case 0x06:
        case 0x07:
            // VSUBBC
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special op VSUBBC\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x08:
        case 0x09:
        case 0x0A:
        case 0x0B:
            // VMADDBC
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special op VMADDBC\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x0C:
        case 0x0D:
        case 0x0E:
        case 0x0F:
            // VMSUBBC
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special op VMSUBBC\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x10:
        case 0x11:
        case 0x12:
        case 0x13:
            // VMAXBC
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special op VMAXBC\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x14:
        case 0x15:
        case 0x16:
        case 0x17:
            // VMINIBC
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special op VMINIBC\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x18:
        case 0x19:
        case 0x1A:
        case 0x1B:
            // VMULBC
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special op VMULBC\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x1C:
            // VMULQ
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special op VMULQ\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x1D:
            // VMAXI
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special op VMAXI\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x1E:
            // VMULI
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special op VMAXI\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x1F:
            // VMINII
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special op VMINII\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x20:
            // VADDQ
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special op VADDQ\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x21:
            // VMADDQ
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special op VMADDQ\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x22:
            // VADDI
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special op VADDI\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x23:
            // VMADDI
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special op VMADDI\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x24:
            // VSUBQ
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special op VSUBQ\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x25:
            // VMSUBQ
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special op VMSUBQ\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x26:
            // VSUBI
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special op VSUBI\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x27:
            // VMSUBI
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special op VMSUBI\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x28:
            // VADD
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special op VADD\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x29:
            // VMADD
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special op VMADDI\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x2A:
            // VMUL
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special op VMUL\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x2B:
            // VMAX
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special op VMAX\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x2C:
            // VSUB
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special op VSUB\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x2D:
            // VMSUB
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special op VMADDI\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x2E:
            // VOPMSUB
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special op VOPMSUB\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x2F:
            // VMINI
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special op VMINI\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x30:
            // VIADD
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special op VIADD\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x31:
            // VISUB
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special op VISUB\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x32:
            // VIADDI
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special op VIADDI\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x34:
            // VIAND
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special op VIAND\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x35:
            // VIOR
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special op VIOR\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x38:
            // VCALLMS
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special op VCALLMS\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x39:
            // VCALLMSR
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special op VCALLMSR\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x3C:
        case 0x3D:
        case 0x3E:
        case 0x3F:
            // COP2 Special2 Operation
            translate_op_cop2_special2(instrs, opcode);
            return;
        default:
            Errors::die("[EE_JIT] Unrecognized cop2 special op $%02X", op);
            return;
    }
    instrs.push_back(instr);
}

void EE_JitTranslator::translate_op_cop2_special2(std::vector<IR::Instruction>& instrs, uint32_t opcode) const
{
    uint8_t op = opcode & 0x3F;
    IR::Instruction instr;

    switch (op)
    {
        case 0x00:
        case 0x01:
        case 0x02:
        case 0x03:
            // VADDABC
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special2 op VADDABC\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x04:
        case 0x05:
        case 0x06:
        case 0x07:
            // VSUBABC
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special2 op VSUBABC\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x08:
        case 0x09:
        case 0x0A:
        case 0x0B:
            // VMADDABC
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special2 op VMADDABC\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x0C:
        case 0x0D:
        case 0x0E:
        case 0x0F:
            // VMSUBABC
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special2 op VMSUBABC\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x10:
            // VITOF0
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special2 op VITOF0\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x11:
            // VITOF4
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special2 op VITOF4\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x12:
            // VITOF12
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special2 op VITOF12\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x13:
            // VITOF15
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special2 op VITOF15\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x14:
            // VFTOI0
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special2 op VFTOI0\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x15:
            // VFTOI4
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special2 op VFTOI4\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x16:
            // VFTOI12
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special2 op VFTOI12\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x17:
            // VFTOI15
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special2 op VFTOI15\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x18:
        case 0x19:
        case 0x1A:
        case 0x1B:
            // VMULABC
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special2 op VMULABC\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x1C:
            // VMULAQ
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special2 op VMULAQ\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x1D:
            // VABS
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special2 op VABS\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x1E:
            // VMULAI
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special2 op VMULAI\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x1F:
            // VCLIP
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special2 op VCLIP\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x20:
            // VADDAQ
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special2 op VADDAQ\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x21:
            // VMADDAQ
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special2 op VMADDAQ\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x23:
            // VMADDAI
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special2 op VMADDAI\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x25:
            // VMSUBAQ
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special2 op VMSUBAQ\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x27:
            // VMSUBAI
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special2 op VMSUBAI\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x28:
            // VADDA
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special2 op VADDA\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x29:
            // VMADDA
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special2 op VMADDA\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x2A:
            // VMULA
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special2 op VMULA\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x2C:
            // VSUBA
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special2 op VSUBA\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x2D:
            // VMSUBA
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special2 op VMSUBA\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x2E:
            // VOPMULA
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special2 op VOPMULA\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x2F:
            // VNOP ?
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special2 op VNOP (?)\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x30:
            // VMOVE
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special2 op VMOVE\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x31:
            // VMR32
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special2 op VMR32\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x34:
            // VLQI
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special2 op VLQI\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x35:
            // VSQI
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special2 op VSQI\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x36:
            // VLQD
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special2 op VLQD\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x37:
            // VSQD
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special2 op VSQD\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x38:
            // VDIV
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special2 op VDIV\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x39:
            // VSQRT
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special2 op VSQRT\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x3A:
            // VRSQRT
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special2 op VRSQRT\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x3B:
            // VWAITQ
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special2 op VWAITQ\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x3C:
            // VMTIR
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special2 op VMTIR\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x3D:
            // VMFIR
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special2 op VMFIR\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x3E:
            // VILWR
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special2 op VILWR\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x3F:
            // VISWR
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special2 op VISWR\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x40:
            // VRNEXT
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special2 op VRNEXT\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x41:
            // VRGET
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special2 op VRGET\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x42:
            // VRINIT
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special2 op VRINIT\n", op);
            fallback_interpreter(instr, opcode);
            break;
        case 0x43:
            // VRXOR
            Errors::print_warning("[EE_JIT] Unrecognized cop2 special2 op VRXOR\n", op);
            fallback_interpreter(instr, opcode);
            break;
        default:
            Errors::die("[EE_JIT] Unrecognized cop2 special2 op $%02X", op);
            return;
    }
    instrs.push_back(instr);
}

// TENTATIVE
bool EE_JitTranslator::is_branch(uint32_t instr_word) const noexcept
{
    uint8_t op = instr_word >> 26;

    switch (op)
    {
        case 0x02:
        case 0x03:
        case 0x04:
        case 0x05:
        case 0x06:
        case 0x07:
        case 0x14:
        case 0x15:
        case 0x16:
        case 0x17:
            return true;
        default:
            break;
    }

    if (op == 0x00)
    {
        op = instr_word & 0x3F;
        switch (op)
        {
            case 0x08:
            case 0x09:
                return true;
            default:
                return false;
        }
    }
    else if (op == 0x01)
    {
        op = (instr_word >> 16) & 0x1F;

        switch (op)
        {
            case 0x00:
            case 0x01:
            case 0x02:
            case 0x03:
            case 0x10:
            case 0x11:
            case 0x12:
            case 0x13:
                return true;
            default:
                return false;
        }
    }

    return false;
}

void EE_JitTranslator::fallback_interpreter(IR::Instruction& instr, uint32_t instr_word) const noexcept
{
    instr.op = IR::Opcode::FallbackInterpreter;
    instr.set_source(instr_word);
}

/**
 * Determine base operation information and which instructions need to be swapped
 */
void EE_JitTranslator::interpreter_pass(EmotionEngine &ee, uint32_t pc)
{
    //TODO
}