from tokenizers import Tokenizer
from tokenizers.models import BPE
from tokenizers.trainers import BpeTrainer
from tokenizers.pre_tokenizers import WhitespaceSplit
from tokenizers.normalizers import NFKC, Lowercase
from tokenizers import normalizers
import glob

# ******** normalizer
tokenizer = Tokenizer(BPE(unk_token="[UNK]"))
trainer = BpeTrainer(vocab_size=32000, show_progress=True,
                     special_tokens=["[UNK]", "[CLS]", "[SEP]", "[PAD]", "[MASK]"])
tokenizer.normalizer = normalizers.Sequence([NFKC(), Lowercase()])
tokenizer.pre_tokenizer = WhitespaceSplit()
#todo add to lower case
files = glob.glob('data/conv/chr*')
tokenizer.train(files, trainer)
tokenizer.save('data/vocab.json')

