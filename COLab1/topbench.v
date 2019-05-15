`timescale 1 ns / 1 ns
module test_tb;
reg src1, src2, less, A_invert, B_invert, cin;
reg[1:0] operation;
wire result,cout;
    alu_top test_top(
       src1,
       src2,
       less,
       A_invert,
       B_invert,
       cin,
       operation,
       result,
       cout
    );
    initial
    begin
        assign src1 = 1;
        assign src2 = 0;
        assign A_invert = 0;
        assign B_invert = 0;
        assign cin = 1;
        assign operation  = 0;

        #5 assign A_invert = 1;

        #5 assign A_invert = 0;
        assign B_invert = 1;

        #5 assign operation = 1;
        #5 assign operation = 2;

        #5 assign cin = 0;
        #5 assign src1 = 0;
        assign src2 = 0;
        assign A_invert = 0;
        assign B_invert = 0;

        //at time 35
        #5 assign src1 = 1;
        assign src2 = 1;
        assign cin = 1;

        #5 assign src1 = 1;
        assign src2 = 0;
        assign cin = 1;

        #5 assign src1 = 0;
        assign src2 = 0;
        assign cin = 1;
        #1
    end

endmodule
