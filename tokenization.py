"""
https://github.com/google/sentencepiece/issues/306
            --unk_piece=[UNK]
            --pad_piece=[PAD]
            --user_defined_symbols=[CLS],[SEP],[MASK]
            for bert with MLM and NSP
"""

import sentencepiece as spm
import glob

files = ','.join(glob.glob('data/conv/chr*'))

spm.SentencePieceTrainer.Train(input=files, model_prefix='chiabert', vocab_size=32000,
                               user_defined_symbols=['[CLS]', '[SEP]', '[MASK]'],
                               unk_piece='[UNK]', pad_piece='[PAD]',
                               character_coverage=1.0, model_type='bpe',
                               num_threads=128)

