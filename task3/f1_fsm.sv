module f1_fsm (
    input   logic       rst,
    input   logic       en,
    input   logic       clk,
    output  logic [7:0] data_out
);
    logic [7:0] state;

    always_ff @(posedge clk, posedge rst)
        if (rst)
            state <= 8'b0;
        else if (en) begin
            if (state == 8'b11111111)
                state <= 8'b0;
            else
                state <= {state[6:0], 1'b1};
        end
            
        
    assign data_out = state;
endmodule
