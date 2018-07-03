solution 'opal_kelly_atis_sepia'
    configurations {'release', 'debug'}
    location 'build'
    project 'opal_kelly_atis_sepia'
        kind 'ConsoleApp'
        language 'C++'
        location 'build'
        files {'source/*.hpp', 'test/*.cpp'}
        libdirs {'resources'}
        links {'opalkellyfrontpanel'}
        defines {'SEPIA_COMPILER_WORKING_DIRECTORY="' .. project().location .. '"'}
        configuration 'release'
            targetdir 'build/release'
            defines {'NDEBUG'}
            flags {'OptimizeSpeed'}
        configuration 'debug'
            targetdir 'build/debug'
            defines {'DEBUG'}
            flags {'Symbols'}
        configuration 'linux'
            links {'pthread'}
            buildoptions {'-std=c++11'}
            linkoptions {'-std=c++11'}
        configuration 'macosx'
            buildoptions {'-std=c++11'}
            linkoptions {'-std=c++11'}
        for index, name in ipairs(configurations()) do
            configuration {'macosx', name}
                postbuildcommands {
                    'install_name_tool -change libopalkellyfrontpanel.dylib '
                    .. path.getabsolute('resources/libopalkellyfrontpanel.dylib')
                    .. ' '
                    .. path.join(path.join(project().location, name), project().name)}
        end
