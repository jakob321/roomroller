# This file is generated by gyp; do not edit.

TOOLSET := target
TARGET := shmnode
DEFS_Debug := \
	'-DNODE_GYP_MODULE_NAME=shmnode' \
	'-DUSING_UV_SHARED=1' \
	'-DUSING_V8_SHARED=1' \
	'-DV8_DEPRECATION_WARNINGS=1' \
	'-DV8_DEPRECATION_WARNINGS' \
	'-DV8_IMMINENT_DEPRECATION_WARNINGS' \
	'-D_LARGEFILE_SOURCE' \
	'-D_FILE_OFFSET_BITS=64' \
	'-D__STDC_FORMAT_MACROS' \
	'-DOPENSSL_THREADS' \
	'-DBUILDING_NODE_EXTENSION' \
	'-DDEBUG' \
	'-D_DEBUG' \
	'-DV8_ENABLE_CHECKS'

# Flags passed to all source files.
CFLAGS_Debug := \
	-fPIC \
	-pthread \
	-Wall \
	-Wextra \
	-Wno-unused-parameter \
	-m64 \
	-fPIC \
	-g \
	-O0

# Flags passed to only C files.
CFLAGS_C_Debug :=

# Flags passed to only C++ files.
CFLAGS_CC_Debug := \
	-fno-rtti \
	-fno-exceptions \
	-std=gnu++1y

INCS_Debug := \
	-I/home/jakob/.cache/node-gyp/12.22.9/include/node \
	-I/home/jakob/.cache/node-gyp/12.22.9/src \
	-I/home/jakob/.cache/node-gyp/12.22.9/deps/openssl/config \
	-I/home/jakob/.cache/node-gyp/12.22.9/deps/openssl/openssl/include \
	-I/home/jakob/.cache/node-gyp/12.22.9/deps/uv/include \
	-I/home/jakob/.cache/node-gyp/12.22.9/deps/zlib \
	-I/home/jakob/.cache/node-gyp/12.22.9/deps/v8/include

DEFS_Release := \
	'-DNODE_GYP_MODULE_NAME=shmnode' \
	'-DUSING_UV_SHARED=1' \
	'-DUSING_V8_SHARED=1' \
	'-DV8_DEPRECATION_WARNINGS=1' \
	'-DV8_DEPRECATION_WARNINGS' \
	'-DV8_IMMINENT_DEPRECATION_WARNINGS' \
	'-D_LARGEFILE_SOURCE' \
	'-D_FILE_OFFSET_BITS=64' \
	'-D__STDC_FORMAT_MACROS' \
	'-DOPENSSL_THREADS' \
	'-DBUILDING_NODE_EXTENSION'

# Flags passed to all source files.
CFLAGS_Release := \
	-fPIC \
	-pthread \
	-Wall \
	-Wextra \
	-Wno-unused-parameter \
	-m64 \
	-fPIC \
	-O3 \
	-fno-omit-frame-pointer

# Flags passed to only C files.
CFLAGS_C_Release :=

# Flags passed to only C++ files.
CFLAGS_CC_Release := \
	-fno-rtti \
	-fno-exceptions \
	-std=gnu++1y

INCS_Release := \
	-I/home/jakob/.cache/node-gyp/12.22.9/include/node \
	-I/home/jakob/.cache/node-gyp/12.22.9/src \
	-I/home/jakob/.cache/node-gyp/12.22.9/deps/openssl/config \
	-I/home/jakob/.cache/node-gyp/12.22.9/deps/openssl/openssl/include \
	-I/home/jakob/.cache/node-gyp/12.22.9/deps/uv/include \
	-I/home/jakob/.cache/node-gyp/12.22.9/deps/zlib \
	-I/home/jakob/.cache/node-gyp/12.22.9/deps/v8/include

OBJS := \
	$(obj).target/$(TARGET)/shm.o

# Add to the list of files we specially track dependencies for.
all_deps += $(OBJS)

# CFLAGS et al overrides must be target-local.
# See "Target-specific Variable Values" in the GNU Make manual.
$(OBJS): TOOLSET := $(TOOLSET)
$(OBJS): GYP_CFLAGS := $(DEFS_$(BUILDTYPE)) $(INCS_$(BUILDTYPE))  $(CFLAGS_$(BUILDTYPE)) $(CFLAGS_C_$(BUILDTYPE))
$(OBJS): GYP_CXXFLAGS := $(DEFS_$(BUILDTYPE)) $(INCS_$(BUILDTYPE))  $(CFLAGS_$(BUILDTYPE)) $(CFLAGS_CC_$(BUILDTYPE))

# Suffix rules, putting all outputs into $(obj).

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(srcdir)/%.cpp FORCE_DO_CMD
	@$(call do_cmd,cxx,1)

# Try building from generated source, too.

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(obj).$(TOOLSET)/%.cpp FORCE_DO_CMD
	@$(call do_cmd,cxx,1)

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(obj)/%.cpp FORCE_DO_CMD
	@$(call do_cmd,cxx,1)

# End of this set of suffix rules
### Rules for final target.
LDFLAGS_Debug := \
	-pthread \
	-rdynamic \
	-m64

LDFLAGS_Release := \
	-pthread \
	-rdynamic \
	-m64

LIBS :=

$(obj).target/shmnode.node: GYP_LDFLAGS := $(LDFLAGS_$(BUILDTYPE))
$(obj).target/shmnode.node: LIBS := $(LIBS)
$(obj).target/shmnode.node: TOOLSET := $(TOOLSET)
$(obj).target/shmnode.node: $(OBJS) FORCE_DO_CMD
	$(call do_cmd,solink_module)

all_deps += $(obj).target/shmnode.node
# Add target alias
.PHONY: shmnode
shmnode: $(builddir)/shmnode.node

# Copy this to the executable output path.
$(builddir)/shmnode.node: TOOLSET := $(TOOLSET)
$(builddir)/shmnode.node: $(obj).target/shmnode.node FORCE_DO_CMD
	$(call do_cmd,copy)

all_deps += $(builddir)/shmnode.node
# Short alias for building this executable.
.PHONY: shmnode.node
shmnode.node: $(obj).target/shmnode.node $(builddir)/shmnode.node

# Add executable to "all" target.
.PHONY: all
all: $(builddir)/shmnode.node

