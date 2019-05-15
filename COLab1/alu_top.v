`timescale 1ns/1ps

module alu_top(
	src1,       //1 bit source 1 (input)
	src2,       //1 bit source 2 (input)
	less,       //1 bit less     (input)
    equal,
	A_invert,   //1 bit A_invert (input)
	B_invert,   //1 bit B_invert (input)
	cin,        //1 bit carry in (input)
    comp,       //3 bit comp     (input)
	operation,  //operation      (input)
	result,     //1 bit result   (output)
	cout       //1 bit carry out(output)
);

input			src1;//lets treat it as A
input			src2;//lets treat it as B
input			less;
input           equal; 
input			A_invert;
input			B_invert;
input			cin;
input   [2:0]   comp;
input	[2-1:0]	operation;

output result;
output cout;

reg result;
reg cout;

wire a;
wire b;
assign a = (A_invert) ? ~src1 : src1;
assign b = (B_invert) ? ~src2 : src2;
always@(*)
begin
    cout <=0;
    case(operation)
        0: result <= a & b; 
        1: result <= a | b; 
        2:begin
            result <= (a ^ b) ^ cin; //XOR for addition with cin
            cout <= (cin & (a | b)) | a & b;//TODO might want to change that a|b to a^b
        end
        3:begin 
            case(comp)
                3'b000:result<=1;//slt(Set less than)
                //3'b001://Sgt(Set great than)
                //3'b010://Sle(set less equal)
                //3'b011://Sge(Set great equal)
                //3'b110://Seq(Set Equal)
                //3'b100://Sne(Set not equal)
            endcase
        end
    endcase
end

endmodule
