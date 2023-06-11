module lcd (
    output reg rs,
    output reg en,
    output reg[7:4] data,
);

    wire clk;
    qlal4s3b_cell_macro u_qlal4s3b_cell_macro (
    	.Sys_Clk0 (clk),
    );

    integer i = 1;
    integer count = 0;
    reg [3:0] nibs [1:51];
    integer a = 9, b = 10;
    reg [7:0] c = a + b, c1, c0, o, a1, a0, b1, b0;

    initial begin
        if (c >= 16) begin
            c = c % 16;
            o = 49;
        end
        else begin
            o = 48;
        end
        c0 = (c % 10) + 48;
        c1 = (c / 10) + 48;
        a0 = (a % 10) + 48;
        a1 = (a / 10) + 48;
        b0 = (b % 10) + 48;
        b1 = (b / 10) + 48;
    end

    always @(posedge clk) begin
        nibs[1]  = 4'h3;
        nibs[2]  = 4'h3;
        nibs[3]  = 4'h3;
        nibs[4]  = 4'h2;
        nibs[5]  = 4'h2;
        nibs[6]  = 4'h8;
        nibs[7]  = 4'h0;
        nibs[8]  = 4'hC;
        nibs[9]  = 4'h0;
        nibs[10] = 4'h6;
        nibs[11] = 4'h0;
        nibs[12] = 4'h1;
        nibs[13] = 4'h8;//Start here
        nibs[14] = 4'h0;
        nibs[15] = 1'b1;
        nibs[16] = 4'h6;
        nibs[17] = 4'h1;//'a'
        nibs[18] = 4'h3;
        nibs[19] = 4'hD;//'='
        nibs[20] = a1[7:4];
        nibs[21] = a1[3:0];//a1
        nibs[22] = a0[7:4];
        nibs[23] = a0[3:0];//a0
        nibs[24] = 4'h2;
        nibs[25] = 4'h0;//' '
        nibs[26] = 4'h6;
        nibs[27] = 4'h2;//'b';
        nibs[28] = 4'h3;
        nibs[29] = 4'hD;//'='
        nibs[30] = b1[7:4];
        nibs[31] = b1[3:0];//b1
        nibs[32] = b0[7:4];
        nibs[33] = b0[3:0];//b0
        nibs[34] = 4'hC;
        nibs[35] = 4'h0;
        nibs[36] = 4'h6;
        nibs[37] = 4'h3;//'c'
        nibs[38] = 4'h3;
        nibs[39] = 4'hD;//'='
        nibs[40] = c1[7:4];
        nibs[41] = c1[3:0];//c1
        nibs[42] = c0[7:4];
        nibs[43] = c0[3:0];//c0
        nibs[44] = 4'h2;
        nibs[45] = 4'h0;//' '
        nibs[46] = 4'h6;
        nibs[47] = 4'hF;//'o'
        nibs[48] = 4'h3;
        nibs[49] = 4'hD;//'='
        nibs[50] = o[7:4];
        nibs[51] = o[3:0];//o
    end
    always @(posedge clk) begin
        if (i<15)
        begin
        	rs<=1'b0;
        	data=nibs[i];
        	en<=1'b1;
        	if (count==800)
            begin
           		en<=1'b0;
           		count<=0;
           		i <= i + 1;
           	end
        	else
           		count<=count+1;
        end
        if (i==15) 
        begin
        	if (count==60000)
            begin
             	count<=0;
             	i<=i+1;
            end
        	else
             	count<=count+1;	
        end
        if ((i>15 && i<34) || (i>35 && i <= 51)) 
        begin 
        	rs<=1'b1;
        	data=nibs[i];
            en<=1'b1;
        	if (count==800)
            begin
        	    en<=1'b0;
        	    count<=0;
                i <= i + 1;
            end
            else
        		count<=count+1;       
        end
        if (i>=34 && i<=35)
        begin
            rs <= 1'b0;
            data = nibs[i];
            en<=1'b1;
        	if (count==800)
            begin
        	    en<=1'b0;
        	    count<=0;
                i <= i + 1;
            end
            else
        		count<=count+1;       
        end
        if (i>51) 
        	i<=13;
    end
endmodule
