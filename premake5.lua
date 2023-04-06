workspace "ClientTest"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "ClientTest"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "ClientTest"