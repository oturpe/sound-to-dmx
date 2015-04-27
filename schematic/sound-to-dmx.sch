<Qucs Schematic 0.0.17>
<Properties>
  <View=0,0,800,800,1,0,0>
  <Grid=10,10,1>
  <DataSet=sound-to-dmx.dat>
  <DataDisplay=sound-to-dmx.dpl>
  <OpenDisplay=1>
  <Script=sound-to-dmx.m>
  <RunScript=0>
  <showFrame=0>
  <FrameText0=Title>
  <FrameText1=Drawn By:>
  <FrameText2=Date:>
  <FrameText3=Revision:>
</Properties>
<Symbol>
  <.PortSym 40 20 1 0>
  <.PortSym 40 60 2 0>
  <.PortSym 40 100 3 0>
  <.PortSym 40 140 4 0>
  <.PortSym 40 180 5 0>
  <.PortSym 40 220 6 0>
  <.PortSym 40 260 8 0>
  <.PortSym 40 300 7 0>
</Symbol>
<Components>
  <C C1 1 90 100 -38 17 0 0 "4.7 nF" 1 "" 0 "neutral" 0>
  <Port LINE_IN_1 1 60 100 -46 -52 0 0 "1" 1 "analog" 0>
  <R R2 1 260 70 -114 -37 0 1 "10 kOhm" 1 "26.85" 0 "0.0" 0 "0.0" 0 "26.85" 0 "european" 0>
  <R R1 1 260 130 -114 -20 0 1 "10 kOhm" 1 "26.85" 0 "0.0" 0 "0.0" 0 "26.85" 0 "european" 0>
  <GND * 1 260 160 0 0 0 0>
  <C C2 1 90 280 -38 17 0 0 "4.7 nF" 1 "" 0 "neutral" 0>
  <Port LINE_IN_2 1 60 280 -46 -52 0 0 "2" 1 "analog" 0>
  <R R3 1 260 250 -114 -37 0 1 "10 kOhm" 1 "26.85" 0 "0.0" 0 "0.0" 0 "26.85" 0 "european" 0>
  <R R4 1 260 310 -114 -20 0 1 "10 kOhm" 1 "26.85" 0 "0.0" 0 "0.0" 0 "26.85" 0 "european" 0>
  <GND * 1 260 340 0 0 0 0>
  <C C3 1 90 460 -38 17 0 0 "4.7 nF" 1 "" 0 "neutral" 0>
  <Port LINE_IN_3 1 60 460 -46 -52 0 0 "3" 1 "analog" 0>
  <R R5 1 260 430 -114 -37 0 1 "10 kOhm" 1 "26.85" 0 "0.0" 0 "0.0" 0 "26.85" 0 "european" 0>
  <R R6 1 260 490 -114 -20 0 1 "10 kOhm" 1 "26.85" 0 "0.0" 0 "0.0" 0 "26.85" 0 "european" 0>
  <GND * 1 260 520 0 0 0 0>
  <C C4 1 90 640 -38 17 0 0 "4.7 nF" 1 "" 0 "neutral" 0>
  <Port LINE_IN_4 1 60 640 -46 -52 0 0 "4" 1 "analog" 0>
  <R R7 1 260 610 -114 -37 0 1 "10 kOhm" 1 "26.85" 0 "0.0" 0 "0.0" 0 "26.85" 0 "european" 0>
  <R R8 1 260 670 -114 -20 0 1 "10 kOhm" 1 "26.85" 0 "0.0" 0 "0.0" 0 "26.85" 0 "european" 0>
  <GND * 1 260 700 0 0 0 0>
  <Vdc V1 1 420 70 18 -26 0 1 "5 V" 1>
  <GND * 1 420 100 0 0 0 0>
  <Port IN_1 1 260 100 18 -47 0 2 "5" 1 "analog" 0>
  <Port IN_2 1 260 280 16 -46 0 2 "6" 1 "analog" 0>
  <Port IN_4 1 260 640 21 -49 0 2 "8" 1 "analog" 0>
  <Port IN_3 1 260 460 15 -47 0 2 "7" 1 "analog" 0>
</Components>
<Wires>
  <120 100 260 100 "" 0 0 0 "">
  <120 280 260 280 "" 0 0 0 "">
  <120 460 260 460 "" 0 0 0 "">
  <120 640 260 640 "" 0 0 0 "">
  <260 40 340 40 "" 0 0 0 "">
  <260 400 340 400 "" 0 0 0 "">
  <260 220 340 220 "" 0 0 0 "">
  <340 40 420 40 "" 0 0 0 "">
  <340 40 340 220 "" 0 0 0 "">
  <340 220 340 400 "" 0 0 0 "">
  <250 580 260 580 "" 0 0 0 "">
  <340 400 340 580 "" 0 0 0 "">
  <260 580 340 580 "" 0 0 0 "">
</Wires>
<Diagrams>
</Diagrams>
<Paintings>
</Paintings>
