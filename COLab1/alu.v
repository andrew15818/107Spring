`timescale 1ns/1ps

//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date:    15:15:11 03/21/2019
// Design Name:
// Module Name:    alu
// Project Name:
// Target Devices:
// Tool versions:
// Description:
//
// Dependencies:
//
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
//
//////////////////////////////////////////////////////////////////////////////////

module alu(
           rst_n,         // negative reset            (input)
           src1,          // 32 bits source 1          (input)
           src2,          // 32 bits source 2          (input)
           ALU_control,   // 4 bits ALU control input  (input)
		   bonus_control, // 3 bits bonus control input(input) 
           result,        // 32 bits result            (output)
           zero,          // 1 bit when the output is 0, zero must be set (output)
           cout,          // 1 bit carry out           (output)
           overflow       // 1 bit overflow            (output)
           );


input           rst_n;
input  [32-1:0] src1;
input  [32-1:0] src2;
input   [4-1:0] ALU_control;
input   [3-1:0] bonus_control; 

output [32-1:0] result;
output          zero;
output          cout;
output          overflow;

reg             zero;
reg             overflow;

//Our own regs
reg             A_invert; 
reg             B_invert; 
reg             cin;//This can be used for twos complement
wire     [32-1:0] mulCout; //check why this has to be wire and not register
reg     [1:0]   subOp;



alu_top alut_top_0(
    .src1(src1[0]),
    .src2(src2[0]),
    .less(result[31]),//I think this is what it is
    .equal(1'b0),//TODO change this to actually do something
    .A_invert(A_invert),
    .B_invert(B_invert),
    .cin(cin),
    .comp(bonus_control),
    .operation(subOp),
    .result(result[0]),
    .cout(mulCout[0])
    );
genvar ind;
generate
    for(ind =1;ind<32;ind= ind+1) begin:for_i
        alu_top alut_top_i(
        .src1(src1[ind]),
        .src2(src2[ind]),
        .less(1'b0),
        .equal(1'b0),//TODO change this to actually do something
        .A_invert(A_invert),
        .B_invert(B_invert),
        .cin(mulCout[ind-1]),
        .comp(bonus_control),
        .operation(subOp),
        .result(result[ind]),
        .cout(mulCout[ind])
    );
end

endgenerate

always @(*) begin
    case(ALU_control)
        4'b0000 : begin//AND
            A_invert = 1'b0;
            B_invert = 1'b0;
            cin = 1'b0;
            subOp = 2;
        end
        4'b0001 : //OR
            A_invert = 1'b0;
        4'b0010 : begin//Addition
            A_invert = 1'b0;
            B_invert = 1'b0;
            cin =1'b0;
            subOp = 0;
            end
        4'b0110 : //Subctract
            A_invert = 1'b0;
        4'b1100 : //Nor
            A_invert = 1'b0;
        4'b1101 : //Nand
            A_invert = 1'b0;
        4'b0111 : //Set Less than
            A_invert = 1'b0;
    endcase
end
endmodule
