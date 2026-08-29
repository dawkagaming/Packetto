cmake_minimum_required(VERSION 3.31)

find_program(GLIB_COMPILE_RESOURCES glib-compile-resources REQUIRED)
find_program(GLIB_COMPILE_SCHEMAS glib-compile-schemas REQUIRED)

function(glib_compile_resources)
    set(flags
        GENERATE_HEADER
        MANUAL_REGISTER
        INTERNAL
        EXTERNAL_DATA)
    set(args
        MIN_VERSION
        CNAME
        SOURCEDIR
        TARGET
        FILE
        OUTPUT_VAR)
    set(listArgs)

    cmake_parse_arguments(arg "${flags}" "${args}" "${listArgs}" ${ARGN})

    # Check version
    if(arg_MIN_VERSION)
        execute_process(COMMAND "${GLIB_COMPILE_RESOURCES}" "--version" OUTPUT_VARIABLE GLIB_COMPILE_RESOURCES_VERSION OUTPUT_STRIP_TRAILING_WHITESPACE RESULT_VARIABLE EXIT_CODE)

        if(NOT EXIT_CODE EQUAL 0)
            message(FATAL_ERROR "[glib_compile_resources]: glib-compile-resources failed with exit code ${EXIT_CODE} when checking version")
        endif()
        
        if("${GLIB_COMPILE_RESOURCES_VERSION}" VERSION_LESS "${arg_MIN_VERSION}")
            message(FATAL_ERROR "[glib_compile_resources]: Minimum version requested is ${arg_MIN_VERSION}, but found version ${GLIB_COMPILE_RESOURCES_VERSION}, which is lower!")
        endif()
    endif()

    # Check file
    if(NOT IS_READABLE "${arg_FILE}")
        message(FATAL_ERROR "[glib_compile_resources]: The input file provided (${arg_FILE}) is not readable!")
    endif()

    # Check OUTPUT_VAR
    if(NOT arg_OUTPUT_VAR)
        message(FATAL_ERROR "[glib_compile_resources]: OUTPUT_VAR is required!")
    endif()

    # Parse other options
    set(COMMAND_ARGS)

    if(arg_GENERATE_HEADER)
        list(APPEND COMMAND_ARGS "--generate-header")
    endif()

    if(arg_MANUAL_REGISTER)
        list(APPEND COMMAND_ARGS "--manual-register")
    endif()

    if(arg_INTERNAL)
        list(APPEND COMMAND_ARGS "--internal")
    endif()

    if(arg_EXTERNAL_DATA)
        list(APPEND COMMAND_ARGS "--external-data")
    endif()

    if(arg_CNAME)
        list(APPEND COMMAND_ARGS "--c-name" "${arg_CNAME}")
    endif()

    if(NOT arg_SOURCEDIR)
        set(arg_SOURCEDIR ${CMAKE_CURRENT_SOURCE_DIR})
    endif()

    if(IS_DIRECTORY "${arg_SOURCEDIR}")
        list(APPEND COMMAND_ARGS "--sourcedir" "${arg_SOURCEDIR}")
    else()
        message(FATAL_ERROR "[glib_compile_resources]: Path passed as SOURCEDIR (${arg_SOURCEDIR}) is not a proper path!")
    endif()

    if(NOT arg_TARGET)
        set(arg_TARGET "${CMAKE_CURRENT_BINARY_DIR}/gresources.c")
    endif()

    get_filename_component(FILE_EXTENSION "${arg_TARGET}" LAST_EXT)

    if(NOT "${FILE_EXTENSION}" STREQUAL ".c")
        string(APPEND arg_TARGET ".c")
    endif()

    list(APPEND COMMAND_ARGS "--target" "${arg_TARGET}")

    # Execute the command

    list(APPEND COMMAND_ARGS "--generate-source")

    list(APPEND COMMAND_ARGS "${arg_FILE}")

    #execute_process(COMMAND "${GLIB_COMPILE_RESOURCES}" ${COMMAND_ARGS} RESULT_VARIABLE EXIT_CODE)

    add_custom_command(
        COMMAND "${GLIB_COMPILE_RESOURCES}" ${COMMAND_ARGS}
        OUTPUT "${arg_TARGET}"
        DEPENDS "${arg_FILE}"
        CODEGEN
        COMMENT "[glib_compile_resources]: Compiling resources from file ${arg_FILE}"
    )

    #if(EXIT_CODE EQUAL 0)
    #    message(STATUS "[glib_compile_resources]: Successfully compiled resourced to file ${arg_TARGET}")
    #else()
    #    message(FATAL_ERROR "[glib_compile_resources]: glib-compile-resources failed with exit code ${EXIT_CODE}")
    #endif

    set("${arg_OUTPUT_VAR}" "${arg_TARGET}" PARENT_SCOPE)
endfunction()

function(glib_compile_schemas)
    set(flags)
    set(args VERSION)
    set(listArgs)

    cmake_parse_arguments(arg "${flags}" "${args}" "${listArgs}" ${ARGN})

    message(FATAL_ERROR "[glib_compile_schemas]: This function is not yet ready!")
endfunction()