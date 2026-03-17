driver_main:

    call wait_message 
    call handle_device 

    jmp driver_main
