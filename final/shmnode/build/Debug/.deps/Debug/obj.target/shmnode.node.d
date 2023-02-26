cmd_Debug/obj.target/shmnode.node := g++ -o Debug/obj.target/shmnode.node -shared -pthread -rdynamic -m64  -Wl,-soname=shmnode.node -Wl,--start-group Debug/obj.target/shmnode/shm.o -Wl,--end-group 
