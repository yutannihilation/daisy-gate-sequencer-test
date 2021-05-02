# daisy-gate-sequencer-test

## Daisyとは？

* <https://www.electro-smith.com/daisy/daisy>

## 考慮点

* トリガーではなくゲートで動く（長いゲートだとバーストになる）楽器用のシーケンサー
* 長いゲートの場合もPWM（ただし間隔は10ms以上）でコントロールしたい
* 2台を交互に動かす

## 参考リンク

* DaisyExamples:
    * [patch/Sequencer](https://github.com/electro-smith/DaisyExamples/tree/master/patch/Sequencer): 5 Step Sequencer with gate and step outputs.
    * [pod/StepSequencer](https://github.com/electro-smith/DaisyExamples/tree/master/pod/StepSequencer): 8 step Sequencer
* [Bastl Instruments - kompas](https://github.com/bastl-instruments/kompas)
* [Mutable Instruments - Grids](https://github.com/pichenettes/eurorack/tree/master/grids)（ライセンスがGPLなので注意）
* [TomWhitwell/Euclidean-sequencer-](https://github.com/TomWhitwell/Euclidean-sequencer-): Music Things Modularの人
* [LOOK MUM NO COMPUTER - ARDUINO 8 STEP SEQUENCER KEYBOARD](https://www.lookmumnocomputer.com/projects/#/sequencer-keyboard)
