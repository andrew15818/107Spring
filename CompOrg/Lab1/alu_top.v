`timescale 1ns/1ps

module alu_top(
	src1,       //1 bit source 1 (input)
	src2,       //1 bit source 2 (input)
	less,       //1 bit less     (input)
    equal,
    lsb,        //Identify whether or not this is the least significant bit
	A_invert,   //1 bit A_invert (input)
	B_invert,   //1 bit B_invert (input)
	cin,        //1 bit carry in (input)
    comp,       //3 bit comp     (input)
	operation,  //operation      (input)
	result,     //1 bit result   (output)
	cout,       //1 bit carry out(output)
    addition
);

input			src1;//lets treat it as A
input			src2;//lets treat it as B
input			less;
input           equal; 
input           lsb;
input			A_invert;
input			B_invert;
input			cin;
input   [2:0]   comp;
input	[2-1:0]	operation;

output cout;
output result;
output addition;

reg cout;
reg result;
reg addition;

wire compResult;

wire a;
wire b;
assign a = (A_invert) ? ~src1 : src1;
assign b = (B_invert) ? ~src2 : src2;

Compare compare(
    .Compare_sel(comp),
    .equal(equal),
    .less(less),
    .lsb(lsb),
    .result(compResult)
);

always@(*)
begin
    cout <=0;
    addition <= (a ^ b) ^ cin;
    cout <= (cin & (a | b)) | a & b;//TODO might want to change that a|b to a^b
    case(operation)
        0: result <= a & b;//ANDing
        1: result <= a | b;//ORing(inclusive)
        2:begin//Addition
            result <= addition; //XOR for addition with cin
            cout <= (cin & (a | b)) | a & b;
        end
        3:begin//Comparison
            if(lsb == 1'b1) begin
                    result <= compResult;
            end
            else begin
                result <=0;
            end
        end
    endcase
end

endmodule
