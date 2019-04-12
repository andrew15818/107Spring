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

wire zero;
wire [31:0] addition;


//Our own regs
reg             A_invert; 
reg             B_invert; 
reg             src1_bu;//Back up for when we want to use src1 for other operations(like subtration) 
reg             src2_bu;//Back up for when we want to use src2 for other operations(like subtration) 
reg             cin;//This can be used for twos complement
wire     [32-1:0] mulCout; //check why this has to be wire and not register
reg     [1:0]   subOp;

assign zero =  (result == 32'd0);
assign cout = mulCout[31];

alu_top alut_top_0(
    .src1(src1[0]),
    .src2(src2[0]),
    .less(addition[31]),
    .equal(addition==32'd0),
    .lsb(1'b1),
    .A_invert(A_invert),
    .B_invert(B_invert),
    .cin(cin),
    .comp(bonus_control),
    .operation(subOp),
    .result(result[0]),
    .cout(mulCout[0]),
    .addition(addition[0])
    );
genvar ind;
generate
    for(ind =1;ind<32;ind= ind+1) begin:for_i
        alu_top alut_top_i(
        .src1(src1[ind]),
        .src2(src2[ind]),
        .less(1'b0),
        .equal(addition == 0),
        .lsb(1'b0),
        .A_invert(A_invert),
        .B_invert(B_invert),
        .cin(mulCout[ind-1]),
        .comp(bonus_control),
        .operation(subOp),
        .result(result[ind]),
        .cout(mulCout[ind]),
        .addition(addition[ind])
    );
end

endgenerate

always @(*) begin
    case(ALU_control)
        4'b0000 : begin//AND
            A_invert = 1'b0;
            B_invert = 1'b0;
            cin = 1'b0;
            subOp = 0;
        end
        4'b0001 : begin//OR
            A_invert = 1'b0;
            B_invert = 1'b0;
            cin = 1'b0;
            subOp = 1;
        end
        4'b0010 : begin//Addition(Unsigned (I think))
            A_invert = 1'b0;
            B_invert = 1'b0;
            cin =1'b0;
            subOp = 2;
            end
        4'b0110 : begin //Subctract(Unsinged)
            A_invert <= 1'b0;
            B_invert <= 1'b1;
            cin <=1'b1;
            subOp = 2;//Basically adding A and B's Complement
            end
        4'b1100 : begin //Nor
            A_invert = 1'b1;
            B_invert = 1'b1;
            cin = 1'b0;
            subOp = 0;//A'B' = A NOR B
        end
        4'b1101 : begin //Nand
            A_invert = 1'b1;
            B_invert = 1'b1;
            cin = 1'b0;
            subOp = 0;//a'+b' = a nand b
        end
        4'b0111 : begin//Set Less than
            A_invert <= 1'b0;
            B_invert <= 1'b1;
            cin <= 1'b1;
            subOp <= 3;//Add after setting the B to 2s complement -> this will set up the conditions for comparison.
            
            //TODO ahorita solo modifica el lsb del result
            //lo que podriamos hacer para dejar todo en 0 es hacerle and con 00..01 per
            //en el siguiente "computation cycle"
        end
    endcase
end
endmodule
