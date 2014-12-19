cmake_minimum_required(VERSION 2.8)
########### next target ###############
set(alib_C
    chapter_2.c
    chapter_3.c
    chapter_4.c
    chapter_5.c
    diag/contract.c
    lang/algorithm.c
    lang/array.c
    lang/class.c
    lang/compare.c
    lang/equals.c
    lang/hash.c
    lang/math_extended.c
    lang/object.c
    lang/sort.c
    lang/string.c
    main.c
    test/test.c
    test/test_container.c
    test/test_container_values.c
    test/test_sort.c
    util/array_container.c
    util/binary_node.c
    util/binary_tree.c
    util/color_array.c
    util/container.c
    util/dictionary.c
    util/edge_node.c
    util/graph.c
    util/graph_visitor.c
    util/hashtable.c
    util/heap.c
    util/hnode.c
    util/iterable.c
    util/iterator.c
    util/key_value_pair.c
    util/linked_graph.c
    util/linked_queue.c
    util/linked_stack.c
    util/node.c
    util/partial_sum.c
    util/priority_queue.c
    util/queue.c
    util/range_container.c
    util/set.c
    util/sorted_dictionary.c
    util/sorted_set.c
    util/sparse_vector.c
    util/stack.c
    util/tree.c
    util/vector.c)
set(alib_H
    chapter_2.h
    chapter_3.h
    chapter_4.h
    chapter_5.h
    diag/contract.h
    lang/algorithm.h
    lang/array.h
    lang/class.h
    lang/compare.h
    lang/equals.h
    lang/hash.h
    lang/math_extended.h
    lang/object.h
    lang/sort.h
    lang/string.h
    lang/type.h
    lang/unsafe.h
    test/test.h
    test/test_container.h
    test/test_container_values.h
    test/test_sort.h
    util/array_container.h
    util/binary_node.h
    util/binary_tree.h
    util/color_array.h
    util/container.h
    util/dictionary.h
    util/edge_node.h
    util/graph.h
    util/graph_visitor.h
    util/hashtable.h
    util/heap.h
    util/hnode.h
    util/iterable.h
    util/iterator.h
    util/key_value_pair.h
    util/linked_graph.h
    util/linked_queue.h
    util/linked_stack.h
    util/matrix_graph.h
    util/node.h
    util/partial_sum.h
    util/priority_queue.h
    util/queue.h
    util/range_container.h
    util/red_black_tree.h
    util/set.h
    util/sorted_dictionary.h
    util/sorted_set.h
    util/sparse_vector.h
    util/stack.h
    util/tree.h
    util/vector.h)

function(noweb files)
	list(LENGTH files files_length)
	math(EXPR length "${files_length} - 1")
	foreach(i RANGE ${length})
	    list(GET files ${i} path)
	    get_filename_component(name "${path}" NAME)
	    get_filename_component(name_we "${path}" NAME_WE)
	    get_filename_component(directory "${path}" DIRECTORY)
	    set(NW_name "${name_we}.nw")
	    if(directory)
		set(NW_path "${directory}/${NW_name}")
	    else(directory)
		set(NW_path "${NW_name}") 
	    endif(directory)
	    add_custom_command(
		    OUTPUT ${path}
		    PRE_BUILD
		    COMMAND notangle -R${name} ${NW_path} > ${path}
	    )
	endforeach(i)
endfunction(noweb)

noweb("${alib_H}")
noweb("${alib_C}")
add_custom_target(generate_alib DEPENDS ${alib_H} ${alib_C})

add_executable(alib ${alib_C})
add_dependencies(alib generate_alib)

target_link_libraries(alib m)
