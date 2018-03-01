#!/bin/bash

export OUTPUTPREFIX="myoutput"

while [[ $# -gt 1 ]]
do
key="$1"

case $key in
  -i )
  export INPUTFILE="$2"
  shift
  ;;
  -o )
  export OUTPUTPREFIX="$2"
  shift
  ;;
  *)
  ;;
esac
shift
done

export SCRIPTDIR=`dirname $0`

#Enu
rm myefficiencyEnu.root
root -l -q $INPUTFILE $SCRIPTDIR/../efficiencies/efficiencyEnu.C
mv myefficiencyEnu.root ${OUTPUTPREFIX}_efficiencyEnu.root

rm mypurityEnu.root
root -l -q $INPUTFILE $SCRIPTDIR/../purities/purityEnu.C
mv mypurityEnu.root ${OUTPUTPREFIX}_purityEnu.root

#rm mybgefficiencyEnu.root
#root -l -q $INPUTFILE $SCRIPTDIR/../bgEfficiencies/bgEfficiencyEnu.C
#mv mybgefficiencyEnu.root ${OUTPUTPREFIX}_bgefficiencyEnu.root
rm mybgefficiencyEnu.root
root -l -q $INPUTFILE $SCRIPTDIR/../bgRejections/bgRejectionEnu.C
mv myBGRejectionEnu.root ${OUTPUTPREFIX}_bgRejectionEnu.root


root -l -q "$SCRIPTDIR/effPurBGEffComparison.C(\"${OUTPUTPREFIX}_efficiencyEnu.root\",\"${OUTPUTPREFIX}_purityEnu.root\",\"${OUTPUTPREFIX}_bgRejectionEnu.root\",\"${OUTPUTPREFIX}_effPurBGRejComparison_Enu\")"


##Q2
#rm myefficiencyQ2.root
#root -l -q $INPUTFILE $SCRIPTDIR/../efficiencies/efficiencyQ2.C
#mv myefficiencyQ2.root ${OUTPUTPREFIX}_efficiencyQ2.root
#
#rm mypurityQ2.root
#root -l -q $INPUTFILE $SCRIPTDIR/../purities/purityQ2.C
#mv mypurityQ2.root ${OUTPUTPREFIX}_purityQ2.root
#
#rm mybgefficiencyQ2.root
#root -l -q $INPUTFILE $SCRIPTDIR/../bgEfficiencies/bgEfficiencyQ2.C
#mv mybgefficiencyQ2.root ${OUTPUTPREFIX}_bgefficiencyQ2.root
#
#root -l -q "$SCRIPTDIR/effPurBGEffComparison.C(\"${OUTPUTPREFIX}_efficiencyQ2.root\",\"${OUTPUTPREFIX}_purityQ2.root\",\"${OUTPUTPREFIX}_bgefficiencyQ2.root\",\"${OUTPUTPREFIX}_effPurBGEffComparison_Q2\")"
#
#
##LepMom
#rm myefficiencyLepMom.root
#root -l -q $INPUTFILE $SCRIPTDIR/../efficiencies/efficiencyLepMom.C
#mv myefficiencyLepMom.root ${OUTPUTPREFIX}_efficiencyLepMom.root
#
#rm mypurityLepMom.root
#root -l -q $INPUTFILE $SCRIPTDIR/../purities/purityLepMom.C
#mv mypurityLepMom.root ${OUTPUTPREFIX}_purityLepMom.root
#
#rm mybgefficiencyLepMom.root
#root -l -q $INPUTFILE $SCRIPTDIR/../bgEfficiencies/bgEfficiencyLepMom.C
#mv mybgefficiencyLepMom.root ${OUTPUTPREFIX}_bgefficiencyLepMom.root
#
#root -l -q "$SCRIPTDIR/effPurBGEffComparison.C(\"${OUTPUTPREFIX}_efficiencyLepMom.root\",\"${OUTPUTPREFIX}_purityLepMom.root\",\"${OUTPUTPREFIX}_bgefficiencyLepMom.root\",\"${OUTPUTPREFIX}_effPurBGEffComparison_LepMom\")"
#
#
##LepAngle
#rm myefficiencyLepAngle.root
#root -l -q $INPUTFILE $SCRIPTDIR/../efficiencies/efficiencyLepAngle.C
#mv myefficiencyLepAngle.root ${OUTPUTPREFIX}_efficiencyLepAngle.root
#
#rm mypurityLepAngle.root
#root -l -q $INPUTFILE $SCRIPTDIR/../purities/purityLepAngle.C
#mv mypurityLepAngle.root ${OUTPUTPREFIX}_purityLepAngle.root
#
#rm mybgefficiencyLepAngle.root
#root -l -q $INPUTFILE $SCRIPTDIR/../bgEfficiencies/bgEfficiencyLepAngle.C
#mv mybgefficiencyLepAngle.root ${OUTPUTPREFIX}_bgefficiencyLepAngle.root
#
#root -l -q "$SCRIPTDIR/effPurBGEffComparison.C(\"${OUTPUTPREFIX}_efficiencyLepAngle.root\",\"${OUTPUTPREFIX}_purityLepAngle.root\",\"${OUTPUTPREFIX}_bgefficiencyLepAngle.root\",\"${OUTPUTPREFIX}_effPurBGEffComparison_LepAngle\")"
#
#
