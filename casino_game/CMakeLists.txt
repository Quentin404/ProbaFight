# Fonction qui ajoute tous les fichiers .cpp et .h aux sources
function(add_sources_to_target target_name)
  file(GLOB_RECURSE sources LIST_DIRECTORIES true *.cpp *.h)

  foreach(source ${sources})
    if(IS_DIRECTORY ${source})
      continue()
    endif()

    target_sources(${target_name} PRIVATE ${source})
  endforeach()
endfunction()

add_executable(casino_game main.cpp)
add_sources_to_target(casino_game)