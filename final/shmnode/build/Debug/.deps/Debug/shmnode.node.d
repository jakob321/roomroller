cmd_Debug/shmnode.node := ln -f "Debug/obj.target/shmnode.node" "Debug/shmnode.node" 2>/dev/null || (rm -rf "Debug/shmnode.node" && cp -af "Debug/obj.target/shmnode.node" "Debug/shmnode.node")
