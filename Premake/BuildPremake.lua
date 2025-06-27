workspace ("InterstellarEngine")
    location ("../") --directory above the Premake directory, the root directory
    architecture ("x86_64")
    configurations {"Debug", "Release"}
    startproject ("InterstellarEngine-Editor")
    flags {"MultiProcessorCompile", "ShadowedVariables", "UndefinedIdentifiers"}

local Root_Dir = "../" --directory above the Premake directory, the root directory
local ExternalDir = Root_Dir .. "External/" -- third party libraries directory like GLFW and glm
local InterstellarEngine_Core_Dir = Root_Dir .. "InterstellarEngine-Core/"
local InterstellarEngine_Editor_Dir = Root_Dir .. "InterstellarEngine-Editor/"

project ("InterstellarEngine-Core")
    location (InterstellarEngine_Core_Dir)
    kind ("StaticLib")
    language ("C++")
    cppdialect "C++20"
    staticruntime "off"

    targetdir (Root_Dir .. "Binaries/IE_Core/%{cfg.system}_%{cfg.architecture}/%{cfg.buildcfg}") --example: Binaries/IE_Core/Windows_x86_64/Debug
    objdir (Root_Dir .. "Binaries/IE_Core/%{cfg.system}_%{cfg.architecture}/%{cfg.buildcfg}/obj")

    files {
        InterstellarEngine_Core_Dir .. "**.cpp",
        InterstellarEngine_Core_Dir .. "**.hpp",
        InterstellarEngine_Core_Dir .. "**.h",
        InterstellarEngine_Core_Dir .. "**.cppm",
        InterstellarEngine_Core_Dir .. "**.ixx"
    }

    includedirs {
        InterstellarEngine_Core_Dir .. "Include",
        InterstellarEngine_Core_Dir .. "Modules",
        InterstellarEngine_Core_Dir .. "Source",

        os.getenv("VULKAN_SDK") .. "/Include",
        ExternalDir .. "glfw-3.4.bin.WIN64/include",
        ExternalDir .. "glm",
        ExternalDir .. "stb"
    }

    libdirs{
        os.getenv("VULKAN_SDK") .. "/Lib",
        ExternalDir .. "glfw-3.4.bin.WIN64/lib-vc2022"
    }

    links{
        "glfw3",
        "vulkan-1"
    }

    filter "configurations:Debug"
        runtime "Debug"
        defines {"DEBUG"}
        linktimeoptimization "off"
        optimize "off"
        symbols "full"
        links{ --some extra vulkan stuff, those are the debug version
            "SPIRVd",
            "SPIRV-Toolsd",
            "SPIRV-Tools-diffd",
            "SPIRV-Tools-optd",
            "glslangd",
            "OSDependentd",
            "GenericCodeGend",
            "MachineIndependentd",
            "glslang-default-resource-limitsd"
        }

    filter "configurations:Release"
        runtime "Release"
        defines {"NDEBUG"}
        linktimeoptimization "on"
        optimize "on"
        symbols "off"
        links{ --the same extra vulkan stuff but not debug
            "SPIRV",
            "SPIRV-Tools",
            "SPIRV-Tools-diff",
            "SPIRV-Tools-opt",
            "glslang",
            "OSDependent",
            "GenericCodeGen",
            "MachineIndependent",
            "glslang-default-resource-limits"
        }

    filter {}
    
project ("InterstellarEngine-Editor")
    location (InterstellarEngine_Editor_Dir)
    kind ("ConsoleApp")
    language ("C++")
    cppdialect "C++20"
    staticruntime "off"

    targetdir (Root_Dir .. "Binaries/IE_Editor/%{cfg.system}_%{cfg.architecture}/%{cfg.buildcfg}") --example: Binaries/IE_Editor/Windows_x86_64/Debug
    objdir (Root_Dir .. "Binaries/IE_Editor/%{cfg.system}_%{cfg.architecture}/%{cfg.buildcfg}/obj")

    files {
        InterstellarEngine_Editor_Dir .. "**.cpp",
        InterstellarEngine_Editor_Dir .. "**.hpp",
        InterstellarEngine_Editor_Dir .. "**.h",
        InterstellarEngine_Editor_Dir .. "**.cppm",
        InterstellarEngine_Editor_Dir .. "**.ixx"
    }

    includedirs {
        InterstellarEngine_Core_Dir .. "Include",
        InterstellarEngine_Core_Dir .. "Modules",
        InterstellarEngine_Core_Dir .. "Source",

        os.getenv("VULKAN_SDK") .. "/Include",
        ExternalDir .. "glfw-3.4.bin.WIN64/include",
        ExternalDir .. "glm"
    }

    libdirs{
        Root_Dir .. "Binaries/IE_Core/%{cfg.system}_%{cfg.architecture}/%{cfg.buildcfg}", --InterstellarEngine-Core output directory
        os.getenv("VULKAN_SDK") .. "/Lib",
        ExternalDir .. "glfw-3.4.bin.WIN64/lib-vc2022"
    }

    links {
        "InterstellarEngine-Core",
        "glfw3",
        "vulkan-1"
    }

    filter "configurations:Debug"
        runtime "Debug"
        defines {"DEBUG"}
        linktimeoptimization "off"
        optimize "off"
        symbols "full"

    filter "configurations:Release"
        runtime "Release"
        defines {"NDEBUG"}
        linktimeoptimization "on"
        optimize "on"
        symbols "off"