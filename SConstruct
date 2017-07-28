# Process this file with http://www.scons.org to build FSP

import os
# init Scons
EnsureSConsVersion(1,1)
EnsurePythonVersion(2,2)

# set defaults
PREFIX='/'
VERSION='2.8.1b27_v1.0.10'
EFENCE=False
CLIENTS=True

#env = Environment(CPPPATH=['#/include','#/p2pnat/include'],LIBPATH=['/usr/lib','/usr/local/lib','#/p2pnat/lib/x86'],LIBS='p2pnat',CC = 'gcc',LDFLAGS=['-Wl,-rpath=p2pnat/lib/x86'])
#wroc
#env = Environment(CPPPATH=['#/include','#/p2pnat/include'],LIBPATH=['/usr/lib','/usr/local/lib','/var/lib','#/p2pnat/lib/wroc'],LIBS=['p2pnat','pthread'],CC = 'mipsel-linux-uclibc-gcc');
#om400
env = Environment(CPPPATH=['#/include','#/p2pnat/include'],LIBPATH=['/usr/lib','/usr/local/lib','/var/lib','#/p2pnat/lib/om400'],LIBS=['p2pnat','pthread'],CC = 'arm-none-linux-gnueabi-gcc');
# Import GZip builder
import gzipBuilder
# Import Symlink builder
import symlinkBuilder
env.Append(BUILDERS = {'GZip'  : Builder(action=gzipBuilder.GZip),
                       'Symlink': Builder(action=symlinkBuilder.Symlink)})

env.Append(RPATH = '/var/lib')
# Import environment
from importer import importEnvironment,importVariable
importEnvironment(env,'HOME')
importVariable(env,'CC')
importVariable(env,'CFLAGS','CCFLAGS')
importEnvironment(env,prefix='DISTCC_')
importEnvironment(env,prefix='CCACHE_')
importEnvironment(env,'PATH')

# Turn CPPFLAGS to list, so we can add values to it
env.Append( CPPFLAGS = [])

# Get CC from commandline
if ARGUMENTS.get('CC', 0):
    env.Replace(CC =  ARGUMENTS.get('CC'))

if ARGUMENTS.get('CFLAGS',0):
   env.Replace(CCFLAGS = ARGUMENTS.get('CFLAGS'))
if ARGUMENTS.get('CCFLAGS',0):
   env.Replace(CCFLAGS = ARGUMENTS.get('CCFLAGS'))

# Convert CCFLAGS into list
env.Replace(CCFLAGS = str(env['CCFLAGS']).split(' '))

############  Start configuration   ##############

from maintainer import checkForMaintainerMode
from compilertest import checkForCCOption
from prefix import checkForUserPrefix
from lockprefix import checkForLockPrefix
from locktype import checkForLockingType
from lamerpack import checkForLamerpack
from debugmode import checkForDebugBuild
from timeout import checkForClientTimeout
from relsignals import checkReliableSignals
from mandir import checkForUserMandir
from docdir import checkForUserDocdir
from mandir import autodetectMandir
from clients import checkForBuildingClients
from sysconfdir import checkForUserSysconfdir
from largefiles import enableLargeFiles
from jade import checkDSSSLProcessor
from dsssl import findDocbookStylesheets

conf = Configure(env,{'checkForCCOption':checkForCCOption,
                      'MAINTAINER_MODE':checkForMaintainerMode,
		      'checkForLockPrefix':checkForLockPrefix,
		      'checkPrefix':checkForUserPrefix,
		      'checkForLockingType':checkForLockingType,
		      'checkForLamerPack':checkForLamerpack,
		      'checkForDebugBuild':checkForDebugBuild,
		      'checkForClientTimeout':checkForClientTimeout,
		      'checkReliableSignals':checkReliableSignals,
		      'checkForUserMandir':checkForUserMandir,
		      'checkForUserDocdir':checkForUserDocdir,
		      'autodetectMandir':autodetectMandir,
		      'checkForUserSysconfdir':checkForUserSysconfdir,
		      'checkForBuildingClients':checkForBuildingClients,
		      'checkDSSSLProcessor':checkDSSSLProcessor,
		      'findDocbookStylesheets':findDocbookStylesheets
	 	      })
if not conf.CheckCC(): Exit(1)
# check for CC options
for option in Split("""
      -Wall -W -Wstrict-prototypes -Wmissing-prototypes -Wshadow
      -Wbad-function-cast -Wcast-qual -Wcast-align -Wwrite-strings
      -Waggregate-return -Wmissing-declarations
      -Wmissing-format-attribute -Wnested-externs
      -ggdb -fno-common -Wchar-subscripts -Wcomment
      -Wimplicit -Wsequence-point -Wreturn-type
      -Wfloat-equal -Wno-system-headers -Wredundant-decls
      -pedantic
      -Wlong-long -Wundef -Winline
      -Wpointer-arith -Wno-unused-parameter
      -Wunreachable-code
      -fmacro-backtrace-limit=2 -Wno-cast-align -Wno-pointer-sign
"""):
       conf.checkForCCOption(option)
if conf.checkDSSSLProcessor("jade"):
    JADE = "jade"
elif conf.checkDSSSLProcessor("openjade"):
    JADE = "openjade"
else:
    JADE = False
if JADE:
    DSSSL = conf.findDocbookStylesheets()
else:
    DSSSL = None
if DSSSL == None:
   JADE = False

# Portability build time config
if conf.CheckFunc('srandomdev'):
    conf.env.Append(CPPFLAGS = '-DHAVE_SRANDOMDEV')
if conf.CheckFunc('random'):
    conf.env.Append(CPPFLAGS = '-DHAVE_RANDOM')
if conf.CheckFunc('fork'):
    conf.env.Append(CPPFLAGS = '-DHAVE_FORK')
if conf.CheckFunc('setsid'):
    conf.env.Append(CPPFLAGS = '-DHAVE_SETSID')
if conf.CheckCHeader('unistd.h'):
    conf.env.Append(CPPFLAGS = '-DHAVE_UNISTD_H')
if conf.CheckCHeader('limits.h'):
    conf.env.Append(CPPFLAGS = '-DHAVE_LIMITS_H')
if conf.CheckCHeader('strings.h'):
    conf.env.Append(CPPFLAGS = '-DHAVE_STRINGS_H')
if conf.CheckCHeader('sys/resource.h'):
    conf.env.Append(CPPFLAGS = '-DHAVE_SYS_RESOURCE_H')
if conf.CheckCHeader('sys/syslimits.h'):
    conf.env.Append(CPPFLAGS = '-DHAVE_SYS_SYSLIMITS_H')
if conf.CheckCHeader('sys/wait.h'):
    conf.env.Append(CPPFLAGS = '-DHAVE_SYS_WAIT_H')
if conf.CheckCHeader('utime.h'):
    conf.env.Append(CPPFLAGS = '-DHAVE_UTIME_H')
if conf.CheckCHeader('utmpx.h'):
    conf.env.Append(CPPFLAGS = '-DHAVE_UTMPX_H')    
if not conf.CheckType("union semun", "#include <sys/types.h>\n#include <sys/ipc.h>\n#include <sys/sem.h>",'c'):
       conf.env.Append(CPPFLAGS = "-D_SEM_SEMUN_UNDEFINED=1")
enableLargeFiles(conf)
conf.checkForLockingType(conf)
if conf.checkReliableSignals():
    conf.env.Append(CPPFLAGS = '-DRELIABLE_SIGNALS')
conf.checkForLockPrefix()
PREFIX=conf.checkPrefix(PREFIX)
conf.checkForUserSysconfdir(PREFIX)
MANDIR=conf.autodetectMandir(PREFIX)
MANDIR=conf.checkForUserMandir(MANDIR)
DOCDIR=PREFIX+'/share/doc/fsp'
DOCDIR=conf.checkForUserDocdir(DOCDIR)
dmode=conf.checkForDebugBuild()
EFENCE = conf.MAINTAINER_MODE(dmode)
if EFENCE == True:
    EFENCE=conf.CheckLib("efence","EF_Abort")
conf.checkForLamerPack()
CLIENTS=conf.checkForBuildingClients()
conf.checkForClientTimeout()
conf.Finish()

env.Append(CPPFLAGS = "-DPACKAGE_VERSION=\\\""+VERSION+"\\\"")
# process build rules
Export( Split("env PREFIX MANDIR DOCDIR CLIENTS JADE DSSSL"))
env.SConscript(dirs=Split("doc . bsd_src common server client clients contrib tests man"))
