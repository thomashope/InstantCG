local p = premake

-- options

newoption {
	trigger = "platform",
	value = "VALUE",
	description = "Platform to package / publish",
	default = "current",
	allowed = {
		{"current", "Package for the current platform, mac or windows."},
		{"emscripten", "Emscripten web build."},
		{"source", "Package source code as .zip archive."}
	}
}


newoption {
	trigger = "graphics",
	value = "VALUE",
	description = "Graphics Backend to Use",
	default = "default",
	allowed = {
		{"default", "default for the current platform"},
		{"d3d11", "DirectX 11 Backend"},
		{"opengl", "OpenGL Backend"},
	}
}

function getGraphicsBackend()
	local defaults = {
		windows = "d3d11",
		macosx = "opengl",
	}

	local backend = _OPTIONS['graphics']

	if backend == 'default' then
		return defaults[_TARGET_OS]
	else
		return backend
	end
end

-- package action

newaction {
	trigger = "package",
	description = "Package game for distribution",

	execute = function()
		assertOptionIsSet('platform')
		
		local platform = _OPTIONS['platform']
		local unsupported = "Action '".._ACTION.."' does not support this OS: '".._TARGET_OS.."', with platform: '"..platform.."'"


		if _TARGET_OS == "macosx" then
			if platform == "current" then
				assertConfigHasKey('appName')
				assertConfigHasKey('appleBundleId')
				assertConfigHasKey('appleDevelopmentTeam')
				assertConfigHasKey('appleUsername')
				assertConfigHasKey('appleAppSpecificPassword')

				os.executef([[tools/scripts/package_mac.sh "%s" "%s" "%s" "%s" "%s"]],
					config.appName,
					config.appleBundleId,
					config.appleDevelopmentTeam,
					config.appleUsername,
					config.appleAppSpecificPassword
					)
			elseif platform == "emscripten" then
				os.execute("tools/scripts/package_emscripten.sh")
			elseif platform == 'source' then
				os.execute('tools/scripts/package_source.sh')
			else
				print(unsupported)
			end
		elseif _TARGET_OS == "windows" then
			if platform == "current" then
				os.executef([[bash ./tools/scripts/package_windows.sh "%s"]],
					config.appName
					)
			else
				-- TODO: support emscripten build on windows
				print(unsupported)
			end
		else
			print(unsupported)
		end
	end,
}

-- publish action

newaction {
	trigger = "publish",
	description = "Publish game to itch.io",

	execute = function()
		assertConfigHasKey('itchUserName')
		assertConfigHasKey('itchGameName')
		
		local platform = _OPTIONS["platform"]
		local unsupported = "Action '".._ACTION.."' does not support this OS: '".._TARGET_OS.."', with platform: '"..platform.."'"

		if _TARGET_OS == "macosx" then
			if platform == "current" then
				os.executef("tools/scripts/publish_mac.sh %s %s", config.itchUserName, config.itchGameName)
			elseif platform == "emscripten" then
				os.executef("tools/scripts/publish_emscripten.sh %s %s", config.itchUserName, config.itchGameName)
			elseif platform == 'source' then
				os.executef("tools/scripts/publish_source.sh %s %s", config.itchUserName, config.itchGameName)
			else
				print(unsupported)
			end
		elseif _TARGET_OS == "windows" then
			if platform == "current" then
				os.execute("bash ./tools/scripts/publish_windows.sh")
			else
				print(unsupported)
			end
		else
			print(unsupported)
		end
	end
}

-- build assets action

newaction {
	trigger = "assets",
	description = "Build game assets",

	execute = function()

		local source_assets = os.matchfiles("assets/source/**")
		local built_assets = os.matchfiles("assets/built/**")

		-- strip junk file names
		local function removeBadFiles(files)
			for i=#files,1,-1 do
				local name = path.getname(files[i])
				if name == ".DS_Store" or name == "icon.png" then
					table.remove(files, i)
				end
			end
		end

		removeBadFiles(source_assets)
		removeBadFiles(built_assets)

		print("\n# Cleaning Built Assets Folder")

		-- remove built assets no longer present in source
		for i,built in ipairs(built_assets) do
			local src = built:gsub("assets/built", "assets/source")
			if not table.contains(source_assets, src) then
				print("removing", built)
				if not os.remove(built) then
					printError("ERROR: failed to remove file: "..built)
				end
			end
		end

		print("\n# Building Assets")

		-- copy over source assets that are newer
		for i,src in ipairs(source_assets) do
			local dst = src:gsub("assets/source", "assets/built")
			local copy = false
			local reason = ""

			-- if the destination file does not exist, do the copy
			if not os.isfile(dst) then
				reason = "(File missing)"
				copy = true
			end

			-- if the destination file does exist, check the size and time stamp to decide if we should copy
			if not copy then
				local src_info = os.stat(src)
				local dst_info = os.stat(dst)

				if not src_info then printError("ERROR: failed to read file stats of: "..src) end
				if not dst_info then printError("ERROR: failed to read file stats of: "..dst) end

				if src_info.size ~= dst_info.size or src_info.mtime >= dst_info.mtime then
					reason = "(File out of date)"
					copy = true
				end
			end

			-- do the copy
			if copy then
				print("Copying:", src, "->", dst, reason)
				makeDirectoriesForFile(dst)
				local ok, err = os.copyfile(src, dst)
				if not ok then
					printError(err)
				end
			end
		end

		print("\n# Done Building Assets")
	end
}

-- clean action

newaction {
	trigger = "clean",
	description = "Delete generated files",

	execute = function()
		os.rmdir("bin")
		os.rmdir("build")
		os.rmdir("package")
		os.rmdir("assets/built")
	end,
}