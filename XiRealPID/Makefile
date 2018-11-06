
APP_NAME      := vertex_rec
SOURCE_FILES  := analysis.cc def_cuts.cc 
INSTALL_DIR   := .

USES_RFIO     := no
USES_ORACLE   := yes
USES_GFORTRAN := yes
HOME:=/u/knowakow


include $(HADDIR)/hades.def.mk

#LIB_DIRS += $(PLUTODIR) ${HOME}/usr/lib64
#INC_DIRS += ${HOME}/usr/include
#HYDRA_LIBS    += -lParticleEvent
LIBS    += -lSpectrum



.PHONY:  default
default: build install
print-%  : ; @echo $* = $($*)

#default: clean build install

include $(HADDIR)/hades.app.mk

