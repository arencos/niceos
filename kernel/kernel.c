#include "../cpu/isr.h"
#include "../drivers/screen.h"
#include "kernel.h"
#include "../libc/string.h"
#include "../libc/mem.h"
#include <stdint.h>


void kernel_main() {
    isr_install();
    irq_install();

    asm("int $2");
    asm("int $3");

    clear_screen();

    kprint("Welcome to NiceOS!\n");
    kprint("Type HELP for a list of commands.\n> ");
}

void user_input(char *input) {
    if (strcmp(input, "HALT") == 0) {
        kprint("System Halted!\n");
        asm volatile("hlt");
    } else if (strcmp(input, "PAGE") == 0) {
        uint32_t phys_addr;
        uint32_t page = kmalloc(1000, 1, &phys_addr);
        char page_str[16] = "";
        hex_to_ascii(page, page_str);
        char phys_str[16] = "";
        hex_to_ascii(phys_addr, phys_str);
        kprint("Page: ");
        kprint(page_str);
        kprint(", physical address: ");
        kprint(phys_str);
        kprint("\n");
    } else if (strcmp(input, "CLS") == 0)
    { 
        clear_screen();
    }
    else if(strcmp(input, "") == 0){
        kprint("");
    }
    else if(strcmp(input, "HELP") == 0){
        kprint("All commands in this OS as of this version!\n");
        kprint("/*-----------------------------------------*/\n");
        kprint("CLS          : Clears the screen!\n");
        kprint("PAGE         : Shows Page info. For debugging purpose only!\n");
        kprint("HALT         : Halts the CPU!\n");
        kprint("ABOUT        : Shows information about the OS\n");
    }
    else if(strcmp(input, "ABOUT") == 0){
        kprint("NiceOS Alpha!\n");
        kprint("Version 2.09\n");
        kprint("(C) NiceOS Team!\n");
    }
    else if(strcmp(input, "CLEAR") == 0)
    { 
        clear_screen();
    }
    else if(strcmp(input, "HELLO") == 0)
    { 
        kprint("Hello, World!\n");
    }
    else if(strcmp(input, "SHELL") == 0)
    { 
        kprint("I see you are excited for a shell, but it is on its way!\n");
    }
    else
    {
        kprint("Command: '");
        kprint(input);
        kprint("' not found.\n");
    }
    
    
    kprint("> ");
}
