cmake_minimum_required(VERSION 3.31)

find_program(GLIB_COMPILE_RESOURCES_BINARY glib-compile-resources REQUIRED)
find_program(GLIB_COMPILE_SCHEMAS_BINARY glib-compile-schemas REQUIRED)

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

    if(NOT IS_ABSOLUTE "${arg_FILE}")
        set(arg_FILE "${CMAKE_CURRENT_SOURCE_DIR}/${arg_FILE}")
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
    set(COMMON_ARGS)

    if(arg_MANUAL_REGISTER)
        list(APPEND COMMON_ARGS "--manual-register")
    endif()

    if(arg_INTERNAL)
        list(APPEND COMMON_ARGS "--internal")
    endif()

    if(arg_EXTERNAL_DATA)
        list(APPEND COMMON_ARGS "--external-data")
    endif()

    if(arg_CNAME)
        list(APPEND COMMON_ARGS "--c-name" "${arg_CNAME}")
    endif()

    if(NOT arg_SOURCEDIR)
        get_filename_component(arg_SOURCEDIR "${arg_FILE}" DIRECTORY)
    endif()

    if(IS_DIRECTORY "${arg_SOURCEDIR}")
        list(APPEND COMMON_ARGS "--sourcedir" "${arg_SOURCEDIR}")
    else()
        message(FATAL_ERROR "[glib_compile_resources]: Path passed as SOURCEDIR (${arg_SOURCEDIR}) is not a proper path!")
    endif()

    if(NOT arg_TARGET)
        set(arg_TARGET "${CMAKE_CURRENT_BINARY_DIR}/gresources.c")

        message(STATUS "TARGET not set, defaulting to ${arg_TARGET}")
    endif()

    get_filename_component(FILE_EXTENSION "${arg_TARGET}" LAST_EXT)

    if(NOT "${FILE_EXTENSION}" STREQUAL ".c")
        string(APPEND arg_TARGET ".c")
    endif()

    list(APPEND SOURCE_ARGS ${COMMON_ARGS} "--target" "${arg_TARGET}" "--generate-source")

    # Execute the command
    add_custom_command(
        OUTPUT "${arg_TARGET}"
        COMMAND "${GLIB_COMPILE_RESOURCES_BINARY}" ${SOURCE_ARGS} "${arg_FILE}"
        DEPENDS "${arg_FILE}"
        CODEGEN
        COMMENT "[glib_compile_resources]: Compiling resources from file ${arg_FILE} into source file: ${arg_TARGET}"
    )

    if(arg_GENERATE_HEADER)
        get_filename_component(TARGET_DIR "${arg_TARGET}" DIRECTORY)

        get_filename_component(TARGET_HEADER "${arg_TARGET}" NAME_WLE)
        
        set(TARGET_HEADER "${TARGET_DIR}/${TARGET_HEADER}.h")

        list(APPEND HEADER_ARGS ${COMMON_ARGS} "--target" "${TARGET_HEADER}" "--generate-header")

        add_custom_command(
            OUTPUT "${TARGET_HEADER}"
            COMMAND "${GLIB_COMPILE_RESOURCES_BINARY}" ${HEADER_ARGS} "${arg_FILE}"
            DEPENDS "${arg_FILE}"
            CODEGEN
            COMMENT "[glib_compile_resources]: Compiling resources from file ${arg_FILE} into header file: ${TARGET_HEADER}"
        )
    endif()


    list(APPEND OUTPUT_FILES "${arg_TARGET}" "${TARGET_HEADER}")

    set("${arg_OUTPUT_VAR}" "${OUTPUT_FILES}" PARENT_SCOPE)
endfunction()

function(glib_compile_schemas)
    set(flags)
    set(args VERSION)
    set(listArgs)

    cmake_parse_arguments(arg "${flags}" "${args}" "${listArgs}" ${ARGN})

    message(FATAL_ERROR "[glib_compile_schemas]: This function is not yet ready!")
endfunction()