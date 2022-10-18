
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

        filter "action:xcode*"        


            links {
                "libs/sdl2/macos/SDL2.framework",    -- relative path to third party frameworks
                "CoreFoundation.framework",                 -- no path needed for system frameworks
                "OpenGL.framework",
            }

            sysincludedirs {
                "libs/sdl2/macos/SDL2.framework/Headers",    -- need to explicitly add path to framework headers
            }

            frameworkdirs {
                "libs/sdl2/macos/",  -- path to search for third party frameworks
            }

            embedAndSign {
                "SDL2.framework",    -- bundle the framework into the built .app and sign with your certificate
            }

            xcodebuildsettings {
                ["MACOSX_DEPLOYMENT_TARGET"] = "10.11",
                ["CODE_SIGN_STYLE"] = "Automatic",
                ["GENERATE_INFOPLIST_FILE"] = "YES",
                ["LD_RUNPATH_SEARCH_PATHS"] = "$(inherited) @executable_path/../Frameworks", -- tell the executable where to find the frameworks. Path is relative to executable location inside .app bundle
            }

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
-- AddProject "input"
AddProject "plasma"
AddProject "noise"