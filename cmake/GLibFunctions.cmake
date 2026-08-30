cmake_minimum_required(VERSION 3.31)

find_program(GLIB_COMPILE_RESOURCES_BINARY glib-compile-resources REQUIRED)
find_program(GLIB_COMPILE_SCHEMAS_BINARY glib-compile-schemas REQUIRED)

function(glib_compile_resources)
    set(flags
        GRESOURCE_BUNDLE)
    set(args
        C_NAME
        FILE
        OUTPUT_VAR)
    set(listArgs
        EXTRA_ARGS
        DEPENDENCIES
        SOURCE_DIR)

    cmake_parse_arguments(arg "${flags}" "${args}" "${listArgs}" ${ARGN})

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

    # Assemble command options
    set(COMMON_ARGS)

    list(APPEND COMMON_ARGS ${arg_EXTRA_ARGS})

    if(arg_C_NAME)
        list(APPEND COMMON_ARGS "--c-name" "${arg_C_NAME}")
    endif()

    if(arg_SOURCE_DIR)
        foreach(DIR_TO_CHECK "${arg_SOURCE_DIR}")
            if(NOT IS_ABSOLUTE "${DIR_TO_CHECK}")
                set(DIR_TO_CHECK "${CMAKE_CURRENT_SOURCE_DIR}/${DIR_TO_CHECK}")
            endif()

            if(IS_DIRECTORY "${DIR_TO_CHECK}")
                list(APPEND COMMON_ARGS "--sourcedir" "${DIR_TO_CHECK}")
            else()
                message(FATAL_ERROR "[glib_compile_resources]: Path passed to SOURCE_DIR (${DIR_TO_CHECK}) is not a proper directory path!")
            endif()
        endforeach()
    else()
        get_filename_component(arg_SOURCE_DIR "${arg_FILE}" DIRECTORY)

        list(APPEND COMMON_ARGS "--sourcedir" "${arg_SOURCE_DIR}")
    endif()

    # Get dependent files list
    set(DEPENDENT_FILES)

    list(APPEND DEPENDENT_FILES ${arg_DEPENDENCIES} "${arg_FILE}")

    execute_process(COMMAND "${GLIB_COMPILE_RESOURCES_BINARY}" ${COMMON_ARGS} "--generate-dependencies" "${arg_FILE}" OUTPUT_VARIABLE GENERATED_DEPENDENCIES OUTPUT_STRIP_TRAILING_WHITESPACE RESULT_VARIABLE EXIT_CODE)

    if(NOT EXIT_CODE EQUAL 0)
        message(FATAL_ERROR "[glib_compile_resources]: glib-compile-resources failed with exit code ${EXIT_CODE} when getting dependent files!")
    endif()

    string(REGEX REPLACE "\r\n|\n" ";" GENERATED_DEPENDENCIES "${GENERATED_DEPENDENCIES}")

    list(APPEND DEPENDENT_FILES ${GENERATED_DEPENDENCIES})

    # Get input file directory and its name without extensions
    get_filename_component(FILE_NAME "${arg_FILE}" NAME_WE)

    # Final execution
    if(arg_GRESOURCE_BUNDLE)
        set(TARGET_GRESOURCE "${CMAKE_CURRENT_BINARY_DIR}/${FILE_NAME}.gresource")

        list(APPEND GRESOURCE_ARGS ${COMMON_ARGS} "--target" "${TARGET_GRESOURCE}")

        add_custom_command(
            OUTPUT "${TARGET_GRESOURCE}"
            COMMAND "${GLIB_COMPILE_RESOURCES_BINARY}" ${GRESOURCE_ARGS} "${arg_FILE}"
            DEPENDS ${DEPENDENT_FILES}
            CODEGEN
            COMMENT "[glib_compile_resources]: Compiling resources from file ${arg_FILE}"
        )

        list(APPEND OUTPUT_TARGETS "${TARGET_GRESOURCE}")
        set("${arg_OUTPUT_VAR}" "${OUTPUT_TARGETS}" PARENT_SCOPE)
    else()
        set(TARGET_SOURCE "${CMAKE_CURRENT_BINARY_DIR}/${FILE_NAME}.c")
        list(APPEND SOURCE_ARGS ${COMMON_ARGS} "--generate-source" "--target" "${TARGET_SOURCE}")

        set(TARGET_HEADER "${CMAKE_CURRENT_BINARY_DIR}/${FILE_NAME}.h")
        list(APPEND HEADER_ARGS ${COMMON_ARGS} "--generate-header" "--target" "${TARGET_HEADER}")

        add_custom_command(
            OUTPUT "${TARGET_SOURCE}" "${TARGET_HEADER}"
            COMMAND "${GLIB_COMPILE_RESOURCES_BINARY}" ${SOURCE_ARGS} "${arg_FILE}"
            COMMAND "${GLIB_COMPILE_RESOURCES_BINARY}" ${HEADER_ARGS} "${arg_FILE}"
            DEPENDS ${DEPENDENT_FILES}
            CODEGEN
            COMMENT "[glib_compile_resources]: Compiling resources from file ${arg_FILE}"
        )

        list(APPEND OUTPUT_TARGETS "${TARGET_SOURCE}" "${TARGET_HEADER}")
        set("${arg_OUTPUT_VAR}" "${OUTPUT_TARGETS}" PARENT_SCOPE)
    endif()
endfunction()

function(glib_compile_schemas)
    set(flags)
    set(args VERSION)
    set(listArgs)

    cmake_parse_arguments(arg "${flags}" "${args}" "${listArgs}" ${ARGN})

    message(FATAL_ERROR "[glib_compile_schemas]: This function is not yet ready!")
endfunction()