# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.3

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/yocto/Desktop/greenfeed/greenfeed_serv

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yocto/Desktop/greenfeed/greenfeed_serv/build

# Include any dependencies generated for this target.
include CMakeFiles/greenfeed_comm_server_iot.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/greenfeed_comm_server_iot.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/greenfeed_comm_server_iot.dir/flags.make

CMakeFiles/greenfeed_comm_server_iot.dir/main.c.o: CMakeFiles/greenfeed_comm_server_iot.dir/flags.make
CMakeFiles/greenfeed_comm_server_iot.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yocto/Desktop/greenfeed/greenfeed_serv/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/greenfeed_comm_server_iot.dir/main.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/greenfeed_comm_server_iot.dir/main.c.o   -c /home/yocto/Desktop/greenfeed/greenfeed_serv/main.c

CMakeFiles/greenfeed_comm_server_iot.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/greenfeed_comm_server_iot.dir/main.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/yocto/Desktop/greenfeed/greenfeed_serv/main.c > CMakeFiles/greenfeed_comm_server_iot.dir/main.c.i

CMakeFiles/greenfeed_comm_server_iot.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/greenfeed_comm_server_iot.dir/main.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/yocto/Desktop/greenfeed/greenfeed_serv/main.c -o CMakeFiles/greenfeed_comm_server_iot.dir/main.c.s

CMakeFiles/greenfeed_comm_server_iot.dir/main.c.o.requires:

.PHONY : CMakeFiles/greenfeed_comm_server_iot.dir/main.c.o.requires

CMakeFiles/greenfeed_comm_server_iot.dir/main.c.o.provides: CMakeFiles/greenfeed_comm_server_iot.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/greenfeed_comm_server_iot.dir/build.make CMakeFiles/greenfeed_comm_server_iot.dir/main.c.o.provides.build
.PHONY : CMakeFiles/greenfeed_comm_server_iot.dir/main.c.o.provides

CMakeFiles/greenfeed_comm_server_iot.dir/main.c.o.provides.build: CMakeFiles/greenfeed_comm_server_iot.dir/main.c.o


CMakeFiles/greenfeed_comm_server_iot.dir/src/manage_upstream.c.o: CMakeFiles/greenfeed_comm_server_iot.dir/flags.make
CMakeFiles/greenfeed_comm_server_iot.dir/src/manage_upstream.c.o: ../src/manage_upstream.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yocto/Desktop/greenfeed/greenfeed_serv/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/greenfeed_comm_server_iot.dir/src/manage_upstream.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/greenfeed_comm_server_iot.dir/src/manage_upstream.c.o   -c /home/yocto/Desktop/greenfeed/greenfeed_serv/src/manage_upstream.c

CMakeFiles/greenfeed_comm_server_iot.dir/src/manage_upstream.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/greenfeed_comm_server_iot.dir/src/manage_upstream.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/yocto/Desktop/greenfeed/greenfeed_serv/src/manage_upstream.c > CMakeFiles/greenfeed_comm_server_iot.dir/src/manage_upstream.c.i

CMakeFiles/greenfeed_comm_server_iot.dir/src/manage_upstream.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/greenfeed_comm_server_iot.dir/src/manage_upstream.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/yocto/Desktop/greenfeed/greenfeed_serv/src/manage_upstream.c -o CMakeFiles/greenfeed_comm_server_iot.dir/src/manage_upstream.c.s

CMakeFiles/greenfeed_comm_server_iot.dir/src/manage_upstream.c.o.requires:

.PHONY : CMakeFiles/greenfeed_comm_server_iot.dir/src/manage_upstream.c.o.requires

CMakeFiles/greenfeed_comm_server_iot.dir/src/manage_upstream.c.o.provides: CMakeFiles/greenfeed_comm_server_iot.dir/src/manage_upstream.c.o.requires
	$(MAKE) -f CMakeFiles/greenfeed_comm_server_iot.dir/build.make CMakeFiles/greenfeed_comm_server_iot.dir/src/manage_upstream.c.o.provides.build
.PHONY : CMakeFiles/greenfeed_comm_server_iot.dir/src/manage_upstream.c.o.provides

CMakeFiles/greenfeed_comm_server_iot.dir/src/manage_upstream.c.o.provides.build: CMakeFiles/greenfeed_comm_server_iot.dir/src/manage_upstream.c.o


CMakeFiles/greenfeed_comm_server_iot.dir/parson/parson.c.o: CMakeFiles/greenfeed_comm_server_iot.dir/flags.make
CMakeFiles/greenfeed_comm_server_iot.dir/parson/parson.c.o: ../parson/parson.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yocto/Desktop/greenfeed/greenfeed_serv/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/greenfeed_comm_server_iot.dir/parson/parson.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/greenfeed_comm_server_iot.dir/parson/parson.c.o   -c /home/yocto/Desktop/greenfeed/greenfeed_serv/parson/parson.c

CMakeFiles/greenfeed_comm_server_iot.dir/parson/parson.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/greenfeed_comm_server_iot.dir/parson/parson.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/yocto/Desktop/greenfeed/greenfeed_serv/parson/parson.c > CMakeFiles/greenfeed_comm_server_iot.dir/parson/parson.c.i

CMakeFiles/greenfeed_comm_server_iot.dir/parson/parson.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/greenfeed_comm_server_iot.dir/parson/parson.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/yocto/Desktop/greenfeed/greenfeed_serv/parson/parson.c -o CMakeFiles/greenfeed_comm_server_iot.dir/parson/parson.c.s

CMakeFiles/greenfeed_comm_server_iot.dir/parson/parson.c.o.requires:

.PHONY : CMakeFiles/greenfeed_comm_server_iot.dir/parson/parson.c.o.requires

CMakeFiles/greenfeed_comm_server_iot.dir/parson/parson.c.o.provides: CMakeFiles/greenfeed_comm_server_iot.dir/parson/parson.c.o.requires
	$(MAKE) -f CMakeFiles/greenfeed_comm_server_iot.dir/build.make CMakeFiles/greenfeed_comm_server_iot.dir/parson/parson.c.o.provides.build
.PHONY : CMakeFiles/greenfeed_comm_server_iot.dir/parson/parson.c.o.provides

CMakeFiles/greenfeed_comm_server_iot.dir/parson/parson.c.o.provides.build: CMakeFiles/greenfeed_comm_server_iot.dir/parson/parson.c.o


CMakeFiles/greenfeed_comm_server_iot.dir/src/parse_upstream_json.c.o: CMakeFiles/greenfeed_comm_server_iot.dir/flags.make
CMakeFiles/greenfeed_comm_server_iot.dir/src/parse_upstream_json.c.o: ../src/parse_upstream_json.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yocto/Desktop/greenfeed/greenfeed_serv/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/greenfeed_comm_server_iot.dir/src/parse_upstream_json.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/greenfeed_comm_server_iot.dir/src/parse_upstream_json.c.o   -c /home/yocto/Desktop/greenfeed/greenfeed_serv/src/parse_upstream_json.c

CMakeFiles/greenfeed_comm_server_iot.dir/src/parse_upstream_json.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/greenfeed_comm_server_iot.dir/src/parse_upstream_json.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/yocto/Desktop/greenfeed/greenfeed_serv/src/parse_upstream_json.c > CMakeFiles/greenfeed_comm_server_iot.dir/src/parse_upstream_json.c.i

CMakeFiles/greenfeed_comm_server_iot.dir/src/parse_upstream_json.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/greenfeed_comm_server_iot.dir/src/parse_upstream_json.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/yocto/Desktop/greenfeed/greenfeed_serv/src/parse_upstream_json.c -o CMakeFiles/greenfeed_comm_server_iot.dir/src/parse_upstream_json.c.s

CMakeFiles/greenfeed_comm_server_iot.dir/src/parse_upstream_json.c.o.requires:

.PHONY : CMakeFiles/greenfeed_comm_server_iot.dir/src/parse_upstream_json.c.o.requires

CMakeFiles/greenfeed_comm_server_iot.dir/src/parse_upstream_json.c.o.provides: CMakeFiles/greenfeed_comm_server_iot.dir/src/parse_upstream_json.c.o.requires
	$(MAKE) -f CMakeFiles/greenfeed_comm_server_iot.dir/build.make CMakeFiles/greenfeed_comm_server_iot.dir/src/parse_upstream_json.c.o.provides.build
.PHONY : CMakeFiles/greenfeed_comm_server_iot.dir/src/parse_upstream_json.c.o.provides

CMakeFiles/greenfeed_comm_server_iot.dir/src/parse_upstream_json.c.o.provides.build: CMakeFiles/greenfeed_comm_server_iot.dir/src/parse_upstream_json.c.o


CMakeFiles/greenfeed_comm_server_iot.dir/src/print_upstream_packet.c.o: CMakeFiles/greenfeed_comm_server_iot.dir/flags.make
CMakeFiles/greenfeed_comm_server_iot.dir/src/print_upstream_packet.c.o: ../src/print_upstream_packet.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yocto/Desktop/greenfeed/greenfeed_serv/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/greenfeed_comm_server_iot.dir/src/print_upstream_packet.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/greenfeed_comm_server_iot.dir/src/print_upstream_packet.c.o   -c /home/yocto/Desktop/greenfeed/greenfeed_serv/src/print_upstream_packet.c

CMakeFiles/greenfeed_comm_server_iot.dir/src/print_upstream_packet.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/greenfeed_comm_server_iot.dir/src/print_upstream_packet.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/yocto/Desktop/greenfeed/greenfeed_serv/src/print_upstream_packet.c > CMakeFiles/greenfeed_comm_server_iot.dir/src/print_upstream_packet.c.i

CMakeFiles/greenfeed_comm_server_iot.dir/src/print_upstream_packet.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/greenfeed_comm_server_iot.dir/src/print_upstream_packet.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/yocto/Desktop/greenfeed/greenfeed_serv/src/print_upstream_packet.c -o CMakeFiles/greenfeed_comm_server_iot.dir/src/print_upstream_packet.c.s

CMakeFiles/greenfeed_comm_server_iot.dir/src/print_upstream_packet.c.o.requires:

.PHONY : CMakeFiles/greenfeed_comm_server_iot.dir/src/print_upstream_packet.c.o.requires

CMakeFiles/greenfeed_comm_server_iot.dir/src/print_upstream_packet.c.o.provides: CMakeFiles/greenfeed_comm_server_iot.dir/src/print_upstream_packet.c.o.requires
	$(MAKE) -f CMakeFiles/greenfeed_comm_server_iot.dir/build.make CMakeFiles/greenfeed_comm_server_iot.dir/src/print_upstream_packet.c.o.provides.build
.PHONY : CMakeFiles/greenfeed_comm_server_iot.dir/src/print_upstream_packet.c.o.provides

CMakeFiles/greenfeed_comm_server_iot.dir/src/print_upstream_packet.c.o.provides.build: CMakeFiles/greenfeed_comm_server_iot.dir/src/print_upstream_packet.c.o


CMakeFiles/greenfeed_comm_server_iot.dir/src/free_upstream_packet.c.o: CMakeFiles/greenfeed_comm_server_iot.dir/flags.make
CMakeFiles/greenfeed_comm_server_iot.dir/src/free_upstream_packet.c.o: ../src/free_upstream_packet.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yocto/Desktop/greenfeed/greenfeed_serv/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/greenfeed_comm_server_iot.dir/src/free_upstream_packet.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/greenfeed_comm_server_iot.dir/src/free_upstream_packet.c.o   -c /home/yocto/Desktop/greenfeed/greenfeed_serv/src/free_upstream_packet.c

CMakeFiles/greenfeed_comm_server_iot.dir/src/free_upstream_packet.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/greenfeed_comm_server_iot.dir/src/free_upstream_packet.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/yocto/Desktop/greenfeed/greenfeed_serv/src/free_upstream_packet.c > CMakeFiles/greenfeed_comm_server_iot.dir/src/free_upstream_packet.c.i

CMakeFiles/greenfeed_comm_server_iot.dir/src/free_upstream_packet.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/greenfeed_comm_server_iot.dir/src/free_upstream_packet.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/yocto/Desktop/greenfeed/greenfeed_serv/src/free_upstream_packet.c -o CMakeFiles/greenfeed_comm_server_iot.dir/src/free_upstream_packet.c.s

CMakeFiles/greenfeed_comm_server_iot.dir/src/free_upstream_packet.c.o.requires:

.PHONY : CMakeFiles/greenfeed_comm_server_iot.dir/src/free_upstream_packet.c.o.requires

CMakeFiles/greenfeed_comm_server_iot.dir/src/free_upstream_packet.c.o.provides: CMakeFiles/greenfeed_comm_server_iot.dir/src/free_upstream_packet.c.o.requires
	$(MAKE) -f CMakeFiles/greenfeed_comm_server_iot.dir/build.make CMakeFiles/greenfeed_comm_server_iot.dir/src/free_upstream_packet.c.o.provides.build
.PHONY : CMakeFiles/greenfeed_comm_server_iot.dir/src/free_upstream_packet.c.o.provides

CMakeFiles/greenfeed_comm_server_iot.dir/src/free_upstream_packet.c.o.provides.build: CMakeFiles/greenfeed_comm_server_iot.dir/src/free_upstream_packet.c.o


CMakeFiles/greenfeed_comm_server_iot.dir/src/manage_downstream.c.o: CMakeFiles/greenfeed_comm_server_iot.dir/flags.make
CMakeFiles/greenfeed_comm_server_iot.dir/src/manage_downstream.c.o: ../src/manage_downstream.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yocto/Desktop/greenfeed/greenfeed_serv/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/greenfeed_comm_server_iot.dir/src/manage_downstream.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/greenfeed_comm_server_iot.dir/src/manage_downstream.c.o   -c /home/yocto/Desktop/greenfeed/greenfeed_serv/src/manage_downstream.c

CMakeFiles/greenfeed_comm_server_iot.dir/src/manage_downstream.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/greenfeed_comm_server_iot.dir/src/manage_downstream.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/yocto/Desktop/greenfeed/greenfeed_serv/src/manage_downstream.c > CMakeFiles/greenfeed_comm_server_iot.dir/src/manage_downstream.c.i

CMakeFiles/greenfeed_comm_server_iot.dir/src/manage_downstream.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/greenfeed_comm_server_iot.dir/src/manage_downstream.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/yocto/Desktop/greenfeed/greenfeed_serv/src/manage_downstream.c -o CMakeFiles/greenfeed_comm_server_iot.dir/src/manage_downstream.c.s

CMakeFiles/greenfeed_comm_server_iot.dir/src/manage_downstream.c.o.requires:

.PHONY : CMakeFiles/greenfeed_comm_server_iot.dir/src/manage_downstream.c.o.requires

CMakeFiles/greenfeed_comm_server_iot.dir/src/manage_downstream.c.o.provides: CMakeFiles/greenfeed_comm_server_iot.dir/src/manage_downstream.c.o.requires
	$(MAKE) -f CMakeFiles/greenfeed_comm_server_iot.dir/build.make CMakeFiles/greenfeed_comm_server_iot.dir/src/manage_downstream.c.o.provides.build
.PHONY : CMakeFiles/greenfeed_comm_server_iot.dir/src/manage_downstream.c.o.provides

CMakeFiles/greenfeed_comm_server_iot.dir/src/manage_downstream.c.o.provides.build: CMakeFiles/greenfeed_comm_server_iot.dir/src/manage_downstream.c.o


CMakeFiles/greenfeed_comm_server_iot.dir/src/send_downstream_message.c.o: CMakeFiles/greenfeed_comm_server_iot.dir/flags.make
CMakeFiles/greenfeed_comm_server_iot.dir/src/send_downstream_message.c.o: ../src/send_downstream_message.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yocto/Desktop/greenfeed/greenfeed_serv/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/greenfeed_comm_server_iot.dir/src/send_downstream_message.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/greenfeed_comm_server_iot.dir/src/send_downstream_message.c.o   -c /home/yocto/Desktop/greenfeed/greenfeed_serv/src/send_downstream_message.c

CMakeFiles/greenfeed_comm_server_iot.dir/src/send_downstream_message.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/greenfeed_comm_server_iot.dir/src/send_downstream_message.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/yocto/Desktop/greenfeed/greenfeed_serv/src/send_downstream_message.c > CMakeFiles/greenfeed_comm_server_iot.dir/src/send_downstream_message.c.i

CMakeFiles/greenfeed_comm_server_iot.dir/src/send_downstream_message.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/greenfeed_comm_server_iot.dir/src/send_downstream_message.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/yocto/Desktop/greenfeed/greenfeed_serv/src/send_downstream_message.c -o CMakeFiles/greenfeed_comm_server_iot.dir/src/send_downstream_message.c.s

CMakeFiles/greenfeed_comm_server_iot.dir/src/send_downstream_message.c.o.requires:

.PHONY : CMakeFiles/greenfeed_comm_server_iot.dir/src/send_downstream_message.c.o.requires

CMakeFiles/greenfeed_comm_server_iot.dir/src/send_downstream_message.c.o.provides: CMakeFiles/greenfeed_comm_server_iot.dir/src/send_downstream_message.c.o.requires
	$(MAKE) -f CMakeFiles/greenfeed_comm_server_iot.dir/build.make CMakeFiles/greenfeed_comm_server_iot.dir/src/send_downstream_message.c.o.provides.build
.PHONY : CMakeFiles/greenfeed_comm_server_iot.dir/src/send_downstream_message.c.o.provides

CMakeFiles/greenfeed_comm_server_iot.dir/src/send_downstream_message.c.o.provides.build: CMakeFiles/greenfeed_comm_server_iot.dir/src/send_downstream_message.c.o


CMakeFiles/greenfeed_comm_server_iot.dir/src/mongo_connector.c.o: CMakeFiles/greenfeed_comm_server_iot.dir/flags.make
CMakeFiles/greenfeed_comm_server_iot.dir/src/mongo_connector.c.o: ../src/mongo_connector.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yocto/Desktop/greenfeed/greenfeed_serv/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object CMakeFiles/greenfeed_comm_server_iot.dir/src/mongo_connector.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/greenfeed_comm_server_iot.dir/src/mongo_connector.c.o   -c /home/yocto/Desktop/greenfeed/greenfeed_serv/src/mongo_connector.c

CMakeFiles/greenfeed_comm_server_iot.dir/src/mongo_connector.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/greenfeed_comm_server_iot.dir/src/mongo_connector.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/yocto/Desktop/greenfeed/greenfeed_serv/src/mongo_connector.c > CMakeFiles/greenfeed_comm_server_iot.dir/src/mongo_connector.c.i

CMakeFiles/greenfeed_comm_server_iot.dir/src/mongo_connector.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/greenfeed_comm_server_iot.dir/src/mongo_connector.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/yocto/Desktop/greenfeed/greenfeed_serv/src/mongo_connector.c -o CMakeFiles/greenfeed_comm_server_iot.dir/src/mongo_connector.c.s

CMakeFiles/greenfeed_comm_server_iot.dir/src/mongo_connector.c.o.requires:

.PHONY : CMakeFiles/greenfeed_comm_server_iot.dir/src/mongo_connector.c.o.requires

CMakeFiles/greenfeed_comm_server_iot.dir/src/mongo_connector.c.o.provides: CMakeFiles/greenfeed_comm_server_iot.dir/src/mongo_connector.c.o.requires
	$(MAKE) -f CMakeFiles/greenfeed_comm_server_iot.dir/build.make CMakeFiles/greenfeed_comm_server_iot.dir/src/mongo_connector.c.o.provides.build
.PHONY : CMakeFiles/greenfeed_comm_server_iot.dir/src/mongo_connector.c.o.provides

CMakeFiles/greenfeed_comm_server_iot.dir/src/mongo_connector.c.o.provides.build: CMakeFiles/greenfeed_comm_server_iot.dir/src/mongo_connector.c.o


# Object files for target greenfeed_comm_server_iot
greenfeed_comm_server_iot_OBJECTS = \
"CMakeFiles/greenfeed_comm_server_iot.dir/main.c.o" \
"CMakeFiles/greenfeed_comm_server_iot.dir/src/manage_upstream.c.o" \
"CMakeFiles/greenfeed_comm_server_iot.dir/parson/parson.c.o" \
"CMakeFiles/greenfeed_comm_server_iot.dir/src/parse_upstream_json.c.o" \
"CMakeFiles/greenfeed_comm_server_iot.dir/src/print_upstream_packet.c.o" \
"CMakeFiles/greenfeed_comm_server_iot.dir/src/free_upstream_packet.c.o" \
"CMakeFiles/greenfeed_comm_server_iot.dir/src/manage_downstream.c.o" \
"CMakeFiles/greenfeed_comm_server_iot.dir/src/send_downstream_message.c.o" \
"CMakeFiles/greenfeed_comm_server_iot.dir/src/mongo_connector.c.o"

# External object files for target greenfeed_comm_server_iot
greenfeed_comm_server_iot_EXTERNAL_OBJECTS =

greenfeed_comm_server_iot: CMakeFiles/greenfeed_comm_server_iot.dir/main.c.o
greenfeed_comm_server_iot: CMakeFiles/greenfeed_comm_server_iot.dir/src/manage_upstream.c.o
greenfeed_comm_server_iot: CMakeFiles/greenfeed_comm_server_iot.dir/parson/parson.c.o
greenfeed_comm_server_iot: CMakeFiles/greenfeed_comm_server_iot.dir/src/parse_upstream_json.c.o
greenfeed_comm_server_iot: CMakeFiles/greenfeed_comm_server_iot.dir/src/print_upstream_packet.c.o
greenfeed_comm_server_iot: CMakeFiles/greenfeed_comm_server_iot.dir/src/free_upstream_packet.c.o
greenfeed_comm_server_iot: CMakeFiles/greenfeed_comm_server_iot.dir/src/manage_downstream.c.o
greenfeed_comm_server_iot: CMakeFiles/greenfeed_comm_server_iot.dir/src/send_downstream_message.c.o
greenfeed_comm_server_iot: CMakeFiles/greenfeed_comm_server_iot.dir/src/mongo_connector.c.o
greenfeed_comm_server_iot: CMakeFiles/greenfeed_comm_server_iot.dir/build.make
greenfeed_comm_server_iot: ../lib/libb64.a
greenfeed_comm_server_iot: CMakeFiles/greenfeed_comm_server_iot.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yocto/Desktop/greenfeed/greenfeed_serv/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking C executable greenfeed_comm_server_iot"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/greenfeed_comm_server_iot.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/greenfeed_comm_server_iot.dir/build: greenfeed_comm_server_iot

.PHONY : CMakeFiles/greenfeed_comm_server_iot.dir/build

CMakeFiles/greenfeed_comm_server_iot.dir/requires: CMakeFiles/greenfeed_comm_server_iot.dir/main.c.o.requires
CMakeFiles/greenfeed_comm_server_iot.dir/requires: CMakeFiles/greenfeed_comm_server_iot.dir/src/manage_upstream.c.o.requires
CMakeFiles/greenfeed_comm_server_iot.dir/requires: CMakeFiles/greenfeed_comm_server_iot.dir/parson/parson.c.o.requires
CMakeFiles/greenfeed_comm_server_iot.dir/requires: CMakeFiles/greenfeed_comm_server_iot.dir/src/parse_upstream_json.c.o.requires
CMakeFiles/greenfeed_comm_server_iot.dir/requires: CMakeFiles/greenfeed_comm_server_iot.dir/src/print_upstream_packet.c.o.requires
CMakeFiles/greenfeed_comm_server_iot.dir/requires: CMakeFiles/greenfeed_comm_server_iot.dir/src/free_upstream_packet.c.o.requires
CMakeFiles/greenfeed_comm_server_iot.dir/requires: CMakeFiles/greenfeed_comm_server_iot.dir/src/manage_downstream.c.o.requires
CMakeFiles/greenfeed_comm_server_iot.dir/requires: CMakeFiles/greenfeed_comm_server_iot.dir/src/send_downstream_message.c.o.requires
CMakeFiles/greenfeed_comm_server_iot.dir/requires: CMakeFiles/greenfeed_comm_server_iot.dir/src/mongo_connector.c.o.requires

.PHONY : CMakeFiles/greenfeed_comm_server_iot.dir/requires

CMakeFiles/greenfeed_comm_server_iot.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/greenfeed_comm_server_iot.dir/cmake_clean.cmake
.PHONY : CMakeFiles/greenfeed_comm_server_iot.dir/clean

CMakeFiles/greenfeed_comm_server_iot.dir/depend:
	cd /home/yocto/Desktop/greenfeed/greenfeed_serv/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yocto/Desktop/greenfeed/greenfeed_serv /home/yocto/Desktop/greenfeed/greenfeed_serv /home/yocto/Desktop/greenfeed/greenfeed_serv/build /home/yocto/Desktop/greenfeed/greenfeed_serv/build /home/yocto/Desktop/greenfeed/greenfeed_serv/build/CMakeFiles/greenfeed_comm_server_iot.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/greenfeed_comm_server_iot.dir/depend

