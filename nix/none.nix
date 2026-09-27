# The "none" container implementation: its archive and LogosContainerImpl config,
# without the contract headers (those are the default package).
{ pkgs, common, src }:

pkgs.stdenv.mkDerivation {
  pname = "${common.pname}-none";
  version = common.version;

  inherit src;
  inherit (common) nativeBuildInputs meta;

  # No tests, so no gtest: this builds where they could not run anyway.
  buildInputs = [ pkgs.nlohmann_json ];
  cmakeFlags = common.cmakeFlags ++ [ "-DLOGOS_CONTAINER_BUILD_TESTS=OFF" ];

  installPhase = ''
    runHook preInstall
    cmake --install . --prefix $out --component none
    runHook postInstall
  '';
}
