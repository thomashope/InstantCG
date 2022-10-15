function loadConfig()
	createConfigIfMissing()
	require "config"
	assertConfigHasKey('appName')
end

function die(msg)
	error('\n\n\t'..msg..'\n')
end

function createConfigIfMissing()
	if not os.isfile('config.lua') then
		io.writefile('config.lua',
[[config = {
	appName = "MyGame",
	
	-- appleUsername = "your_apple_id@gmail.com",
	-- appleAppSpecificPassword = "password123_for_command_line_tools",
	-- appleBundleId = "com.example.MyGame",
	-- appleDevelopmentTeam = "123ABCD123",

	-- itchGameName = "your_itch_game_name",
	-- itchUserName = "your_itch_username",
}]])
		die('config.lua not found! A template config.lua has been created for you.')
	end
end

function assertConfigHasKey(key)
	if not config[key] then
		die('Missing value from config.lua, config.'..key)
	end
end

function assertOptionIsSet(opt)
	if not _OPTIONS[opt] then
		die('Action \''.._ACTION..'\' requires the option --'..opt..' be specified. Use --help for details.')
	end
end

-- ensures directories exist for the given filepath
function makeDirectoriesForFile(filepath)
	local dir = path.getdirectory(filepath)
	if not os.isdir(dir) then
		local ok, err = os.mkdir(dir)
		if not ok then
			printError(err)
		end
	end
end

function printError(msg)
	term.pushColor(term.errorColor)
	print(msg)
	term.popColor()
end