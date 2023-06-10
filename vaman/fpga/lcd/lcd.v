`timescale 1us/1us

module lcd_adder ( 
    output reg [7:4] data,
    output reg en,
    output reg rs,
    input [3:0] a,
    input [3:0] b,
);

    wire clk;
    integer c, d, e;
    qlal4s3b_cell_macro u_qlal4s3b_cell_macro (
    	.Sys_Clk0 (clk),
    );

    // Task to pulse enable line to clock
    // 4 bits into microcontroller.
    task PulseEnableLine;
        begin
            en <= 1;
            #50 en <= 0;
        end
    endtask

    // Task to send byte to LCD
    // lcd_rs = 0 -> command byte
    // lcd_rs = 1 -> data byte
    task SendByte;
        input lcd_rs;
        input [7:0] byte;
        begin
            rs <= lcd_rs;
            data[7:4] <= byte[7:4];
            PulseEnableLine();
            data[7:4] <= byte[3:0];
        end
    endtask

    // Task to output an integer
    // on LCD
    task SendInteger;
        input integer res;
        integer num, digit;
        begin
            num = res;
            while (num) begin
            //for (num = res; num > 0; num = num / 10) begin
                digit = num % 10;
                SendByte(1, 48 + digit);
            end
        end
    endtask

    // Initialize the LCD
    initial begin
        SendByte(0, 8'h33);
        SendByte(0, 8'h32);
        SendByte(0, 8'h28);
        SendByte(0, 8'h0C);
        SendByte(0, 8'h06);
        SendByte(0, 8'h01);
        #3000;
    end

    always @(posedge clk) begin
        SendByte(0, 8'h01);
        // Do computation
        #3000 c = a+b;
        // Send answer to LCD
        d = c % 16;
        e = d % 10;
        d = d / 10;
        SendByte(1, 48+e);
        SendByte(1, 48+d);
        if (c > 15) begin
            SendByte(0, 8'h80);
            SendByte(1, "O");
            SendByte(1, "v");
            SendByte(1, "e");
            SendByte(1, "r");
            SendByte(1, "f");
            SendByte(1, "l");
            SendByte(1, "o");
            SendByte(1, "w");
        end
    end
endmodule
