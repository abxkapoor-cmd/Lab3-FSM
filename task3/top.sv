module top #(

    parameter WIDTH = 16
)(

    input logic [WIDTH-1:0] N,
    input logic en ,
    input logic rst ,
    input logic clk,
    output logic [7:0] data_out
);

    logic tick;

    clktick #(.WIDTH(WIDTH)) my_clktick (
        .clk (clk),
        .rst (rst),
        .en (en),
        .N (N),
        .tick (tick)
    );

    f1_fsm my_fsm (
        .clk (clk),
        .rst (rst),
        .en (tick),
        .data_out (data_out)
    );

endmodule
