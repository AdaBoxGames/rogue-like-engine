project "Anvil"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "src/**.h",
        "src/**.cpp"
    }

    includedirs
    {
        "src",
		"%{lib_includes.glm}",
		"%{lib_includes.ImGui}",
        "%{lib_includes.ImGui}/ImGui",  -- Temporary Fix, doing this because imgui backend files include the root source file directory
		"%{lib_includes.spdlog}",

        -- RLE include
		"%{wks.location}/RogueLikeEngine/src",
    }

    links
    {
		"ImGui",
        "RogueLikeEngine"
    }

	filter "system:windows"
        systemversion "latest"
        defines "RLE_OS_WIN64"

    filter "configurations:Debug"
        defines "RLE_DEBUG"
        symbols "on"

    filter "configurations:Release"
        defines "RLE_RELEASE"
        optimize "on"

    filter "configurations:Dist"
        defines "RLE_DIST"
        optimize "on"