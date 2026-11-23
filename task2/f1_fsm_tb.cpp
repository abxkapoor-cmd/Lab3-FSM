#include "Vf1_fsm.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "../vbuddy.cpp"

int main(int argc, char **argv, char **env) {
    int i;
    int clk;

    Verilated::commandArgs(argc, argv);
    Vf1_fsm* top = new Vf1_fsm;

    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace(tfp, 99);
    tfp->open("f1_fsm.vcd");

    if (vbdOpen() != 1) return -1;
    vbdHeader("F1 FSM");
    vbdSetMode(1);          // flag mode 1: one press = one flag

    top->clk = 1;
    top->rst = 0;
    top->en  = 0;

    for (i = 0; i < 300; i++) {
        for (clk = 0; clk < 2; clk++) {
            tfp->dump(2*i + clk);
            top->clk = !top->clk;
            top->eval();
        }

        vbdBar(top->data_out & 0xFF);   // show lights on the bar
        top->en = vbdFlag();            // switch press drives en

        vbdCycle(i + 1);
        if (Verilated::gotFinish() || vbdGetkey() == 'q') exit(0);
    }

    vbdClose();
    tfp->close();
    exit(0);
}