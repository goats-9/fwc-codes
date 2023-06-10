module decade (
    output a,
    output b,
    output c,
    output d,
    output e,
    output f,
    output g,
);
    reg[26:0] delay;
    reg[7:0] num = 0;
    wire clk;

    qlal4s3b_cell_macro u_qlal4s3b_cell_macro (
        .Sys_Clk0 (clk),
    );

    function automatic [6:0] gpio_out;
    input [6:0] digit;
    begin
        case (digit)
            0 : gpio_out = 7'b0000001;
            1 : gpio_out = 7'b1001111;
            2 : gpio_out = 7'b0010010;
            3 : gpio_out = 7'b0000110;
            4 : gpio_out = 7'b1001100;
            5 : gpio_out = 7'b0100100;
            6 : gpio_out = 7'b0100000;
            7 : gpio_out = 7'b0001111;
            8 : gpio_out = 7'b0000000;
            9 : gpio_out = 7'b0000100;
            default : gpio_out = 7'b1111111; 
        endcase
    end
    endfunction

    always@(posedge clk) 
    begin
    	delay = delay+1;
    	if(delay > 20000000)
    	begin
    		delay=27'b0;
    		num=num+1;
    	end
    	if(num > 9)
    	begin
    		num = 0;
    	end
    end 

    assign {a,b,c,d,e,f,g} = gpio_out(num);
endmodule
