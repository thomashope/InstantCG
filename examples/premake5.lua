
workspace "InstantCG"
    configurations { "Debug", "Release" }
    location ("build/" .. _ACTION)

local function AddProject(name)

    local dir_name = "example_"..name

    project (name)
        kind "WindowedApp"
        location ("build/" .. _ACTION)
        language "C++"
        cppdialect "C++11"
        targetdir ("bin/" .. _ACTION .. name .. "/%{cfg.buildcfg}")
        architecture "x86_64"

        files {
            "../instantcg.h",
            "../instantcg.cpp",

            dir_name.."/*.cpp",
            dir_name.."/*.h",
        }

        sysincludedirs {
            ".."
        }

        -- configuration specific settings
        filter "configurations:Debug"
        
            defines {
                "DEBUG"
            }
            symbols "On"
            targetsuffix "_d"

        filter "configurations:Release"

            defines {
                "NDEBUG"
            }
            optimize "On"


        -- windows specific settings
        filter "action:vs*"

            libdirs {
                "libs/sdl2/windows/lib/x64"
            }

            links {
                "SDL2",
                "SDL2main",
            }

            postbuildcommands {
                "{COPYFILE} %{wks.location}/../../libs/sdl2/windows/lib/x64/SDL2.dll %{cfg.buildtarget.directory}",
            }

            sysincludedirs {
                "libs/sdl2/windows/include"
            }

            flags {
                "MultiProcessorCompile"
            }
end

AddProject "hello_world"
AddProject "fire"
AddProject "input"
AddProject "plasma"
AddProject "textures"