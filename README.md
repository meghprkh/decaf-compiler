# Decaff compiler

## Megh Parikh - 201501184

## Building:
```
cd src
./configure
make
```

## Running: 
```
./helper.sh filename
```

## Outputting AST graphs
- Uncomment line 13 & 14 of `helper.sh`
- Run `./helper.sh filename`
- Requires [mermaid cli](https://github.com/mermaidjs/mermaid.cli) (or you can paste the contents of `tmp.mermaid` [here](https://mermaidjs.github.io/mermaid-live-editor/))