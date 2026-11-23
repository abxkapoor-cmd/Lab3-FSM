#include "Vtop.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "../vbuddy.cpp"

int main(int argc, char **argv, char **env) {
    int i;
    int clk;

    Verilated::commandArgs(argc, argv);
    Vtop* top = new Vtop;

    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace(tfp, 99);
    tfp->open("top.vcd");

    if (vbdOpen() != 1) return -1;
    vbdHeader("L3T3: F1 auto");

    top->clk = 1;
    top->rst = 1;
    top->en  = 1;
    top->N   = 24;

    for (i = 0; i < 1000000; i++) {
        for (clk = 0; clk < 2; clk++) {
            tfp->dump(2*i + clk);
            top->clk = !top->clk;
            top->eval();
        }

        top->rst = (i < 2);               // reset for the first 2 cycles
        top->N   = vbdValue();            // rotary switch sets N
        vbdBar(top->data_out & 0xFF);     // lights on the bar

        vbdCycle(i + 1);
        if (Verilated::gotFinish() || vbdGetkey() == 'q') break;
    }

    vbdClose();
    tfp->close();
    exit(0);
}