{
  description = "C++ Development with Nix in 2023";
  
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
  };


  outputs = { self, nixpkgs}:
  let

    supportedSystems = [ "x86_64-linux" ];

    forAllSystems = nixpkgs.lib.genAttrs supportedSystems;

      # Nixpkgs instantiated for supported system types.
    nixpkgsFor = forAllSystems (system: import nixpkgs { inherit system; });

  in
  {
    # Provide some binary packages for selected system types.
      devShells = forAllSystems (system:
        let pkgs = nixpkgsFor.${system};
        in {
          default = pkgs.callPackage ./shell.nix {};
        });

    };
}