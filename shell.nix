{ pkgs ? import <nixpkgs> {} }:
  pkgs.mkShell{
            nativeBuildInputs = with pkgs;[ cmake pkg-config meson ninja ];
            buildInputs = with pkgs;[ SDL2 eigen ];
            
            
          
}
