module blinkip (
    input ledstate,
    output redled,
    output blueled,
    output greenled,
);

    assign blueled = ledstate;
endmodule
