# shell.nix for your CMake, GLFW, OpenGL project
{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell rec {
  # Name of the development environment
  name = "my-cmake-glfw-opengl-shell";

  # Dependencies for building and running the project
  buildInputs = [
    pkgs.cmake        # CMake for configuring and building the project
    pkgs.gcc          # Compiler (CMake needs this)
    pkgs.glfw-wayland # GLFW library for OpenGL windowing
    #pkgs.opengl      # OpenGL libraries
    pkgs.libGL        # OpenGL runtime
    pkgs.pkg-config   # Optional, useful for finding libraries
  	pkgs.wayland
	pkgs.libxkbcommon
	pkgs.xorg.libX11
	pkgs.xorg.libXrandr
	pkgs.xorg.libXinerama
	pkgs.xorg.libXcursor
	pkgs.xorg.libXi
  ];

  # Environment variables for the shell (if needed)
  shellHook = ''
    echo "Welcome to the development environment for CMake, GLFW, and OpenGL!"
	export LD_LIBRARY_PATH=${pkgs.wayland}/lib:$LD_LIBRARY_PATH
  '';
}
