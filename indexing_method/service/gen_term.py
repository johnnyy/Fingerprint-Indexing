from textwrap import wrap


class generate_term:
    def __init__(self, bits):
        self.bits = bits

    def set_bits(self, bits):
        self.bits = bits

    def generate_terms(self, line):
        values_bit = wrap(line.replace(" ", ""), self.bits)
        return ["{}_{}".format(i, int(x1, 2)) for i, x1 in enumerate(values_bit)]

    def create_terms(self, text):
        terms = self.generate_terms(text)
        return " ".join(terms)
