`timescale 1ns/1ps

module alu_top(
	src1,       //1 bit source 1 (input)
	src2,       //1 bit source 2 (input)
	less,       //1 bit less     (input)
    equal,
    lsb,
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
input           lsb;
input			A_invert;
input			B_invert;
input			cin;
input   [2:0]   comp;
input	[2-1:0]	operation;

output results;
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
        0: result <= a & b;//ANDing
        1: result <= a | b;//ORing(inclusive)
        2:begin//Addition
            result <= (a ^ b) ^ cin; //XOR for addition with cin
            cout <= (cin & (a | b)) | a & b;//TODO might want to change that a|b to a^b
        end
        3:begin//Comparison
            case(comp)
                3'b000: begin
                    if (lsb & less) begin
                        result =1'b1;//slt(Set less than)
                    end
                    else begin
                            result = 1'b0;
                    end
                end
                //3'b001://Sgt(Set great than)
                //3'b010://Sle(set less equal)
                //3'b011://Sge(Set great equal)
                //3'b110://Seq(Set Equal)
                //3'b100://Sne(Set not equal)
            endcase
        end
        default: begin
        end
    endcase
end

endmodule
