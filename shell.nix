{ pkgs ? import <nixpkgs> {} }:
  pkgs.mkShell {
    # nativeBuildInputs is usually what you want -- tools you need to run
    buildInputs = with pkgs.buildPackages; [
    #opencl-headers
    #xorg.libXau
    
    #xorg.libXdmcp
    ];
    nativeBuildInputs = with pkgs.buildPackages; [ glfw gcc_multi gnumake cmake SDL2 SDL2.dev  eigen gdb];
}
