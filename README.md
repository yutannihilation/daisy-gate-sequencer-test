# daisy-gate-sequencer-test

## Daisyとは？

* <https://www.electro-smith.com/daisy/daisy>

## 考慮点

* トリガーではなくゲートで動く楽器用のシーケンサー。
* ゲートはある程度の長さがないと音が鳴らない、長いゲートだとバーストになる。
* ゲートが開始してから音が鳴り始めるまでに100〜200msくらい？（未計測）のラグがある。ラグの長さはおそらくばらつきがあるのできっちりリズムを刻むのは諦める。
* 動かす予定のものは今の所2台。それぞれラグが違うけど、1音目は割と揃いそう。バーストの間隔はそれぞれ違いそう。
* ゲートはPWMも出したい。ただし、ゲートで開閉するリレーの特性上、間隔は10ms以上あける。

## 参考リンク

* DaisyExamples:
    * [patch/Sequencer](https://github.com/electro-smith/DaisyExamples/tree/master/patch/Sequencer): 5 Step Sequencer with gate and step outputs.
    * [pod/StepSequencer](https://github.com/electro-smith/DaisyExamples/tree/master/pod/StepSequencer): 8 step Sequencer
* [Bastl Instruments - kompas](https://github.com/bastl-instruments/kompas)
* [Mutable Instruments - Grids](https://github.com/pichenettes/eurorack/tree/master/grids)（ライセンスがGPLなので注意）
* [TomWhitwell/Euclidean-sequencer-](https://github.com/TomWhitwell/Euclidean-sequencer-): Music Things Modularの人
* [LOOK MUM NO COMPUTER - ARDUINO 8 STEP SEQUENCER KEYBOARD](https://www.lookmumnocomputer.com/projects/#/sequencer-keyboard)
