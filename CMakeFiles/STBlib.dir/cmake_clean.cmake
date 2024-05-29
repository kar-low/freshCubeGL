file(REMOVE_RECURSE
  "libSTBlib.a"
  "libSTBlib.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/STBlib.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
