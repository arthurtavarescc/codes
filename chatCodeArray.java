package minhaLista;

public class MinhaLista {
    
    private Aluno[] lista;
    public static final int CAPACIDADE_DEFAULT = 20;
    private int tamanho;

    public MinhaLista() {
        this(CAPACIDADE_DEFAULT);
    }

    public MinhaLista(int capacidade) {
        this.lista = new Aluno[capacidade];
        this.tamanho = 0;
    }

    public boolean add(Aluno aluno) {
        assegureCapacidade(this.tamanho + 1);
        this.lista[this.tamanho] = aluno;
        this.tamanho++;
        return true;
    }

    public void add(int index, Aluno aluno) {
        if (index < 0 || index > this.tamanho) {
            throw new IndexOutOfBoundsException();
        }

        assegureCapacidade(this.tamanho + 1);
        shiftParaDireita(index);

        this.lista[index] = aluno;
        this.tamanho++;
    }

    public void set(int index, Aluno aluno) {
        if (index < 0 || index >= this.tamanho) {
            throw new IndexOutOfBoundsException();
        }
        this.lista[index] = aluno;
    }

    private void shiftParaDireita(int index) {
        for (int i = this.tamanho; i > index; i--) {
            this.lista[i] = this.lista[i - 1];
        }
    }

    private void shiftParaEsquerda(int index) {
        for (int i = index; i < this.tamanho - 1; i++) {
            this.lista[i] = this.lista[i + 1];
        }
    }

    public void assegureCapacidade(int capacidadePretendida) {
        if (capacidadePretendida > this.lista.length) {
            resize(Math.max(this.lista.length * 2, capacidadePretendida));
        }
    }

    private void resize(int novaCapacidade) {
        Aluno[] novaLista = new Aluno[novaCapacidade];
        for (int i = 0; i < this.tamanho; i++) {
            novaLista[i] = this.lista[i];
        }
        this.lista = novaLista;
    }

    public Aluno remove(int index) {
        if (index < 0 || index >= this.tamanho) {
            return null;
        }
        
        Aluno aluno = this.lista[index];
        shiftParaEsquerda(index);
        this.tamanho--;
        return aluno;
    }

    public boolean remove(Aluno aluno) {
        if (aluno == null) return false;

        for (int i = 0; i < this.tamanho; i++) {
            if (this.lista[i].equals(aluno)) {
                remove(i);
                return true;
            }
        }
        return false;
    }

    public Aluno get(int index) {
        if (index < 0 || index >= this.tamanho) {
            throw new IndexOutOfBoundsException();
        }
        return this.lista[index];
    }

    public int indexOf(Aluno aluno) {
        for (int i = 0; i < this.tamanho; i++) {
            if (this.lista[i].equals(aluno)) {
                return i;
            }
        }
        return -1;
    }

    public boolean contains(Aluno aluno) {
        return this.indexOf(aluno) != -1;
    }
}
