`timescale 1 ns / 1 ns
module test_all;
reg rst_n;
reg [31:0]src1;
reg [31:0]src2;
reg [3:0]ALU_control;
reg [2:0]bonus_control;
wire [31:0] result;
wire zero, cout, overflow;
    alu test_alu_all(
       rst_n,
       src1,
       src2,
       ALU_control,
       bonus_control,
       result,
       zero,
       cout,
       overflow
    );
    initial
    begin
        assign rst_n = 0;
        assign src1 = 8;
        assign src2 = 4;
        assign ALU_control = 4'b0010;
        assign bonus_control = 3'b000;

        #10 assign ALU_control = 4'b0000;
    end

endmodule
